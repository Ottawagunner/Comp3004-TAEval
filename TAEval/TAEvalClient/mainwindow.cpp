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

    //ui->textBrowser->append(ui->selectTestOption->currentText()+" Test");
    switch(ui->selectTestOption->currentIndex()){
    case 0:
        handleLogIn();
        break;
    case 1:
        handleLogOut();
        break;
    case 2:
        handleCreateTask();
        break;
    case 3:
        handleEditTask();
        break;
    case 4:
        handleDeleteTask();
        break;
    case 5:
        handleViewTask();
        break;
    case 6:
        handleCreateEval();
        break;
    case 7:
        handleViewTAs();
        break;
    case 8:
        handleViewCourse();
        break;
    default:
        break;
    }
}
short MainWindow::handleLogIn(){
    ui->textBrowser->append("Login Test Handled");
    return 0;
}
short MainWindow::handleLogOut(){
    ui->textBrowser->append("Logout Test Handled");
    return 0;
}
short MainWindow::handleCreateTask(){
    ui->textBrowser->append("Create Task Test Handled");
    return 0;
}
short MainWindow::handleEditTask(){
    ui->textBrowser->append("Edit Task Test Handled");
    return 0;
}
short MainWindow::handleDeleteTask(){
    ui->textBrowser->append("Delete Task Test Handled");
    return 0;
}
short MainWindow::handleViewTask(){
    ui->textBrowser->append("View Task Test Handled");
    return 0;
}
short MainWindow::handleCreateEval(){
    ui->textBrowser->append("Create Evaluation Test Handled");
    return 0;
}
short MainWindow::handleViewTAs(){
    ui->textBrowser->append("View TA Test Handled");
    return 0;
}
short MainWindow::handleViewCourse(){
    ui->textBrowser->append("View Course Test Handled");
    return 0;
}
