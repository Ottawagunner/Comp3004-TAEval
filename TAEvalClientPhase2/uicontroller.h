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
    std::string currUserType;
    std::string username;
public:
    UIController(ClientControl* mainControl, int argc,char **argv);
    int run();
    void loginNotify();
    void logoutNotify();
    void reqViewCourseList(std::string);
    void reqViewTask(std::string taskID);
    void reqViewAllTasks(std::string courseId);
    void reqViewEval(std::string taskID);
    void reqViewAllEvals();
    void reqAddTask(std::string);
    void reqDeleteTask(std::string);
    void reqEditTask(std::string);
    void reqAddEval(std::string);
    void reqDeleteEval(std::string);
    void reqEditEval(std::string);
    void reqViewAllTAs(std::string);
    void updateList(std::string);
};

#endif // UICONTROLLER_H
