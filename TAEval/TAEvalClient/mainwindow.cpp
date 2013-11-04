#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    options[0] = "Log in";
    options[1] = "Log out";
    options[2] = "Create Task";
    options[3] = "Edit Task";
    options[4] = "Delete Task";
    options[5] = "View Task";
    options[6] = "Create Evaluation";
    options[7] = "View TAs";
    options[8] = "View Course";
    ui->setupUi(this);
    for(short i=0; i<9; ++i){
        ui->selectTestOption->addItem(options[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runTestButton_clicked()
{
    controller->handleRunButton(ui->selectTestOption->currentIndex());
}

void MainWindow::on_selectTestOption_highlighted(const int i)
{
    QString info = ""+i;
    switch(i){
    case 0:
        info = "Login test description";
        break;
    case 1:
        info = "Logout test description";
        break;
    case 2:
        info = "Create task test description";
        break;
    case 3:
        info = "Edit task test description";
        break;
    case 4:
        info = "Delete task test description";
        break;
    case 5:
        info = "View task test description";
        break;
    case 6:
        info = "Evaluation test description";
        break;
    case 7:
        info = "View TAs test description";
        break;
    case 8:
        info = "View course test description";
        break;
    default:
        break;
    }
    ui->description->setText(info);
}

void MainWindow::setController(clientcontroller *c)
{
    controller = c;
}

void MainWindow::writeToDescription(QString str)
{
    ui->description->setText(QString(str));
}

void MainWindow::writeToLog(QString str)
{
    ui->textBrowser->append(QString(str));
}
