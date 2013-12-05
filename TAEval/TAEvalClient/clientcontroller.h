#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H
#include <QtGui/QApplication>
#include <string>
#include <cstdlib>
#include <sstream>
#include <QDebug>
#include "mainwindow.h"
#include "decoder.h"
#include "encoder.h"

class MainWindow;
class clientcontroller
{
public:
    clientcontroller();
    int run(int,char**);
    short handleRunButton(int);

private:
    std::string userName;
    std::string userType;
    Server client;
    MainWindow* window;
    bool loggedIn;

    std::string* handleMessage(std::string);
};

#endif // CLIENTCONTROLLER_H
