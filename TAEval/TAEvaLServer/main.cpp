#include <QtGui/QApplication>
#include "mainwindow.h"
#include "server.h"
#include <QDebug>
#include "Controller.h"

int main(int argc, char *argv[])
{
    std::string fileList[4];
    fileList[0] = "Admin.db";
    fileList[1] = "Instructor.db";
    fileList[2] = "TA.db";
    fileList[3] = "Course.db";
    std::string path = "./Storage/";
    Controller c(4,path,fileList);
    c.runServer();
    //c.executeMessage("Iusername~CreateTaskRequest~Message");
}
