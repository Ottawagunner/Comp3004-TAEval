#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H
#include <QtGui/QApplication>
#include "mainwindow.h"
class MainWindow;
class clientcontroller
{
public:
    clientcontroller();
    int run(int,char**);
    Server client;
    MainWindow* window;

    short handleRunButton(int);

private:
    std::string userName;
    std::string userType;

    short handleLogIn();
    short handleLogOut();
    short handleCreateTask();
    short handleEditTask();
    short handleDeleteTask();
    short handleViewTask();
    short handleCreateEval();
    short handleViewTAs();
    short handleViewCourse();
    std::string  encode(std::string, std::string);
    std::string* parse(std::string, int, bool);
    std::string* handleMessage(std::string);
};

#endif // CLIENTCONTROLLER_H
