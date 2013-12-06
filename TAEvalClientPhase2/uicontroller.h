#ifndef UICONTROLLER_H
#define UICONTROLLER_H
#include <QtGui/QApplication>
#include "instructorview.h"
#include "LoginDialog.h"
#include "taview.h"
#include "clientcontrol.h"
class LoginDialog;
class ClientControl;
class InstructorView;
class TAView;

class UIController
{
private:
    LoginDialog *d;
    ClientControl *control;
    QApplication a;
    InstructorView *i;
    TAView *t;
    char currUserType;
    std::string username;
public:
    UIController(ClientControl* mainControl, int argc,char **argv);
    int run();
    void loginNotify(std::string, char);
    void logoutNotify();
    void reqViewCourseList(std::string);
    void reqViewTask(std::string taskID);
    void reqViewAllTasks();
    void reqViewEval(std::string taskID);
    void reqViewAllEvals();
    void reqAddTask();
    void reqDeleteTask();
    void reqEditTask();
    void reqAddEval();
    void reqDeleteEval();
    void reqEditEval();
    void reqViewAllTAs();
    void updateList(std::string);
};

#endif // UICONTROLLER_H
