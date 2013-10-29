#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    host.Setup();
    while(true){
        QString buffer = QString::fromStdString(host.ReciveText());
        qDebug()<<(buffer);
        host.SendText("Accepted "+buffer.toStdString()+" Request");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
