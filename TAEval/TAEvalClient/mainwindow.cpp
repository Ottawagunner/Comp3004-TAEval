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
        info = "This test sends a request to the server, to look for the username and will reply with a message indicating it's success";
        break;
    case 1:
        info = "This test sends a message to the server that will tell it to close it's current connection. You cannot log out twice";
        break;
    case 2:
        info = "This test sends a message to the server to create a new task with the data provided";
        break;
    case 3:
        info = "This sends a task number and all the changed data to the server which will search for the task and replace it";
        break;
    case 4:
        info = "This deletes a task based on the task provided";
        break;
    case 5:
        info = "This sends a TA name to the server which responds with all the tasks for that TA";
        break;
    case 6:
        info = "This allows the Instructor to write evaluations on existing tasks";
        break;
    case 7:
        info = "By specifying a course code the server responds with all the TAs for that course";
        break;
    case 8:
        info = "By specifying their user name, the Instructor can view all of their courses that they are teaching";
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
