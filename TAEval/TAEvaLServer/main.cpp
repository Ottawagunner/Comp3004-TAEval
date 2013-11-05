#include <QtGui/QApplication>
#include "mainwindow.h"
#include "server.h"
#include <QDebug>
#include "Controller.h"

int main()
{
    std::string fileList[5];
    fileList[0] = "Admin.db";
    fileList[1] = "Instructor.db";
    fileList[2] = "TA.db";
    fileList[3] = "Course.db";
    fileList[4] = "Task.db";
    std::string path = "./Storage/";
    Controller* c = new Controller(5,path,fileList);
    c->runServer();
}
