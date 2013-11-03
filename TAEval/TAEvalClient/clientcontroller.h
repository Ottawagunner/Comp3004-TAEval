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
    std::string* parse(std::string, int);
    void handleMessage(std::string);

private:
    std::string userName;

    short handleLogIn();
    short handleLogOut();
    short handleCreateTask();
    short handleEditTask();
    short handleDeleteTask();
    short handleViewTask();
    short handleCreateEval();
    short handleViewTAs();
    short handleViewCourse();
};

#endif // CLIENTCONTROLLER_H
