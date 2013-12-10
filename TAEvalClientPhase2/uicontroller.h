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
    std::string getUser();

    void loginNotify();
    void logoutNotify();
    void reqViewTask(std::string taskID);
    void reqViewAllTasks(std::string courseId);
    void reqViewEval(std::string taskID);
    void reqViewAllEvals();
    void reqAddTask(std::string,std::string);
    void reqDeleteTask(std::string);
    void reqEditTask(std::string,std::string);
    void reqAddEval(std::string,std::string);
    void reqDeleteEval(std::string);
    void reqEditEval(std::string,std::string);
    void reqViewAllTAs(std::string);

    void updateCourseList(std::string);
    void updateTaskList(std::string);
    void updateListDialogList(std::string);
    void updateIDialog(std::string, std::string);
};

#endif // UICONTROLLER_H
