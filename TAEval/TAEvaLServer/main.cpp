#include <QtGui/QApplication>
#include "mainwindow.h"
#include "server.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    Server host;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
