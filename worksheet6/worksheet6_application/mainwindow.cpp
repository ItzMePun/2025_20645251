#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connect Buttons to Handlers
    connect(ui->RightButton, &QPushButton::released, this, &MainWindow::handleRightButton);
    connect(ui->LeftButton, &QPushButton::released, this, &MainWindow::handleLeftButton);
    
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

        ModelPart* childItem = new ModelPart({ name, visible });
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++)
        {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name, visible });
            childItem->appendChild(childChildItem);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleRightButton()
{
    //QMessageBox msgBox;
    //msgBox.setText("Button was clicked!");
    //msgBox.exec();
    emit statusUpdateMessage(QString("Right Button was clicked"), 0);
}

void MainWindow::handleLeftButton()
{
    //QMessageBox msgBox;
    //msgBox.setText("Button was clicked!");
    //msgBox.exec();
    emit statusUpdateMessage(QString("Left Button was clicked"), 0);
}
