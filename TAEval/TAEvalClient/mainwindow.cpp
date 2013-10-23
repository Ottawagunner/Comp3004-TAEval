#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createTaskButton_clicked()
{
    QMessageBox::information(this,"Create Task Test","Creating a task...");
}

void MainWindow::on_editTaskButton_clicked()
{
    QMessageBox::information(this,"Edit Task Test","Editing a task...");
}

void MainWindow::on_deleteTaskButton_clicked()
{
    QMessageBox::information(this,"Delete Task Test","Deleting a task...");
}

void MainWindow::on_viewCoursesButton_clicked()
{
    QMessageBox::information(this,"View Course Test","Viewing Courses...");
}

void MainWindow::on_viewAsignedTasks_clicked()
{
    QMessageBox::information(this,"View Assigned Tasks Test","Viewing Assigned Tasks...");
}

void MainWindow::on_viewTAButton_clicked()
{
    QMessageBox::information(this,"View TA Test","Viewing TAs...");
}


void MainWindow::on_loginButton_clicked()
{
    QMessageBox::information(this,"Login Test","Logging in...");
}

void MainWindow::on_logoutButton_clicked()
{
    QMessageBox::information(this,"Logout Test","Logging out...");
}

void MainWindow::on_giveEvaluationButton_clicked()
{
    QMessageBox::information(this,"Give Evaluation Test","Giving an Evaluation...");
}
