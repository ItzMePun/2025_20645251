#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelPartList.h"

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
        void handleRightButton();
        void handleLeftButton();

    private:
        Ui::MainWindow *ui;
        ModelPartList* partList;

    signals:
        void statusUpdateMessage(const QString & message, int timeout);
};

#endif // MAINWINDOW_H
