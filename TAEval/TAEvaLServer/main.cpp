#include <QtGui/QApplication>
#include "mainwindow.h"
#include "server.h"
#include <QDebug>
#include "Controller.h"

int main()
{
    std::string* fileList = new std::string[4];
    fileList[0] = "Instructor.db";
    fileList[1] = "TA.db";
    fileList[2] = "Course.db";
    fileList[3] = "Task.db";
    std::string path = "./Storage/";
    Controller* c = new Controller(4,path, fileList);
    c->runServer();
    delete c;
    delete[] fileList;
}
