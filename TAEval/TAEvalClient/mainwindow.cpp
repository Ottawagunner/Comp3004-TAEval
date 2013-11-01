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
    userName = "JohnSmith";

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
    ui->textBrowser->append("Logging in username: JohnSmith");
    client.Setup();
    client.SendText("I"+userName+"~LoginRequest~"+userName);
    ui->textBrowser->append("Request Sent");
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
}
short MainWindow::handleLogOut(){
    client.SendText("I"+userName+"~LogoutRequest~"+userName);
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
}
short MainWindow::handleCreateTask(){
    std::string taskInfo;
    taskInfo = "Please grade all of the tests in your mailbox";
    client.SendText("I"+userName+"~CreateTaskRequest~"+taskInfo);
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
}
short MainWindow::handleEditTask(){
    ui->textBrowser->append("Edit Task Test Handled");
    return 0;//unsure of how this is going to work but its here until we figure it out
}
short MainWindow::handleDeleteTask(){
    client.SendText("I"+userName+"~DeleteTaskRequest~"+"TASK001");
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
}
short MainWindow::handleViewTask(){
    client.SendText("I"+userName+"~ViewTaskRequest~"+"COMP3004");
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
}
short MainWindow::handleCreateEval(){
    client.SendText("I"+userName+"~CreateEvaluationRequest~"+"TASK001");
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
}
short MainWindow::handleViewTAs(){
    client.SendText("I"+userName+"~ViewTARequest~"+"COMP3004");
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
}
short MainWindow::handleViewCourse(){
    client.SendText("I"+userName+"~ViewCoursesRequest~"+userName);
    QString buffer = QString::fromStdString(client.ReciveText());
    ui->textBrowser->append(buffer);
    return 0;
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
