#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelPartList.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCylinderSource.h>
#include <vtkCylinder.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        
        void updateRender();
        void updateRenderFromTree(const QModelIndex&);

    private:
        Ui::MainWindow *ui;
        ModelPartList* partList;
        vtkSmartPointer<vtkRenderer> renderer;
        vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;

    signals:
        void statusUpdateMessage(const QString & message, int timeout);

    public slots:
        void handleRightButton();
        void handleLaunchDialogButton();
        void handleTreeViewClick();
        void on_actionOpen_File_triggered();
        void on_actionSave_File_triggered();
        void on_actionItem_options_triggered();
};

#endif // MAINWINDOW_H
