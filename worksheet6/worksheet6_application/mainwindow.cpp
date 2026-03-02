#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->RightButton, &QPushButton::released, this, &MainWindow::handleRightButton);
    connect(ui->LeftButton, &QPushButton::released, this, &MainWindow::handleLeftButton);
	connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
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
