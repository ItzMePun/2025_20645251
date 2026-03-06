#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include "optiondialog.h"
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connect Buttons to Handlers
    connect(ui->RightButton, &QPushButton::released, this, &MainWindow::handleRightButton);
    connect(ui->OptionDialogButton, &QPushButton::released, this, &MainWindow::handleLaunchDialogButton);

    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeViewClick);

    //Connect Button Handlers to Status Update
	connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);

    //Setup ModelPartList and ModelPart
    this->partList = new ModelPartList("PartsList");
    ui->treeView->setModel(this->partList);
    ModelPart* rootItem = this->partList->getRootItem();

    for (int i = 0; i < 3; i++)
    {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");
        QColor color(0, 0 ,0);

        ModelPart* childItem = new ModelPart({ name, visible, color });
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++)
        {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");
            QColor color(0, 0 ,0);

            ModelPart* childChildItem = new ModelPart({ name, visible, color });
            childItem->appendChild(childChildItem);
        }
    }

    ui->treeView->addAction( ui->actionItem_options );

    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->renderWidget->setRenderWindow(renderWindow);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1., 0., 0.35);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    renderer->AddActor(cylinderActor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleRightButton()
{
    emit statusUpdateMessage(QString("Right Button was clicked"), 0);
}

void MainWindow::handleLaunchDialogButton()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid())
    {
        emit statusUpdateMessage(QString("No item selected"), 0);
        return;
    }
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString name = selectedPart->data(0).toString();
    QString visible = selectedPart->data(1).toString();
    
    // Pass the data to the dialog
    optionDialog dialog(this, selectedPart);
    
    if (dialog.exec() == QDialog::Accepted)
    {
        // Update the model part with new data from dialog
        selectedPart->set(0, dialog.getName());
        selectedPart->set(1, dialog.getVisible());
        selectedPart->set(2, dialog.getColor());
        
        // Notify the model that data has changed
        this->partList->dataChanged(index, index);

        updateRender();
        
        emit statusUpdateMessage(QString("Dialog Accepted - Changes Applied"), 0);
    }
    else
    {
        emit statusUpdateMessage(QString("Dialog Rejected"), 0);
    }
}

void MainWindow::handleTreeViewClick()
{
    QModelIndex index = ui->treeView->currentIndex();
    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
    QString text = selectedPart->data(0).toString();
    emit statusUpdateMessage(QString("The selected item is: ")+text, 0);
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\", tr("STL Files(*.stl);;Text Files(*.txt)"));
    
    if (fileName.isEmpty())
    {
        emit statusUpdateMessage(QString("Openfile has been selected, operation cancelled"), 0);
        return;
    }
    
    emit statusUpdateMessage(QString("Openfile has been selected, choosing file")+fileName, 0);

    QModelIndex index = ui->treeView->currentIndex();
    
    if (!index.isValid())
    {
        emit statusUpdateMessage(QString("ERROR: No item selected in tree!"), 0);
        return;
    }

    ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

    QString name = QString("New Unnamed Part");
    QString visible("true");
    QColor color(100, 0 ,0);

    ModelPart* newPart = new ModelPart({ fileName, visible, color });

    selectedPart->appendChild(newPart);
    newPart->loadSTL(fileName);

    updateRender();
	ui->treeView->expand(index);
    emit statusUpdateMessage(QString("New part added with ") + QString::number(selectedPart->childCount()) + QString(" children"), 0);
}

void MainWindow::updateRender()
{
	renderer->RemoveAllViewProps();

    updateRenderFromTree(QModelIndex());
    
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
    renderWindow->Render();
}

void MainWindow::updateRenderFromTree(const QModelIndex& index)
{
    if (index.isValid())
    {
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
        
        if (selectedPart && (selectedPart->data(1).toString().compare("true", Qt::CaseInsensitive) == 0))
        {
            renderer->AddActor(selectedPart->getActor());
        }
    }

    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren))
    {
        return;
    }

	int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++)
    {
        QModelIndex child = partList->index(i, 0, index);
        if (child.isValid())
        {
            updateRenderFromTree(child);
        }
    }
}


void MainWindow::on_actionSave_File_triggered()
{
    emit statusUpdateMessage(QString("Save File has been selected"), 0);
}



void MainWindow::on_actionItem_options_triggered()
{
    handleLaunchDialogButton();
}

