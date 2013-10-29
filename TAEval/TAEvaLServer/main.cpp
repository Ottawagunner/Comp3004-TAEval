#include <QtGui/QApplication>
#include "mainwindow.h"
#include "server.h"
#include <QDebug>
#include "Controller.h"

int main(int argc, char *argv[])
{
    Controller c;
    c.executeMessage("Iusername~myReq~Message");
    Server host;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
