#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
    Controller c;
    c.handleMessage("5~L~COMP1804~COMP2804~COMP3804~COMP4804~COMP3004");
    c.handleMessage("3~U~Alphonse Brown~Charles Dupont~Elise Festive");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
