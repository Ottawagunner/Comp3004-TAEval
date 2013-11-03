#include "clientcontroller.h"

clientcontroller::clientcontroller(){
    userName = "JohnSmith";
}

int clientcontroller::run(int argc, char **argv){
    QApplication a(argc, argv);
    MainWindow w;
    window = &w;
    w.show();
    w.setController(this);
    return a.exec();
}
short clientcontroller::handleLogIn(){
    QString s ="Logging in username:";//+userName);
    window->writeToLog(s);
    client.Setup();
    client.SendText("I"+userName+"~LoginRequest~"+userName);
    s = "Request Sent";
    window->writeToLog(s);
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleLogOut(){
    client.SendText("I"+userName+"~LogoutRequest~"+userName);
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleCreateTask(){
    std::string taskInfo;
    taskInfo = "Please grade all of the tests in your mailbox";
    client.SendText("I"+userName+"~CreateTaskRequest~"+taskInfo);
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleEditTask(){
    QString s = "Edit Task Test Handled";
    window->writeToLog(s);
    return 0;//unsure of how this is going to work but its here until we figure it out
}
short clientcontroller::handleDeleteTask(){
    client.SendText("I"+userName+"~DeleteTaskRequest~"+"TASK001");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleViewTask(){
    client.SendText("I"+userName+"~ViewTaskRequest~"+"COMP3004");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleCreateEval(){
    client.SendText("I"+userName+"~CreateEvaluationRequest~"+"TASK001");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleViewTAs(){
    client.SendText("I"+userName+"~ViewTARequest~"+"COMP3004");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleViewCourse(){
    client.SendText("I"+userName+"~ViewCoursesRequest~"+userName);
    QString buffer = QString::fromStdString(client.ReciveText());
   window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleRunButton(int index){
    switch(index){
    case 0:
        handleLogIn();
        break;
    case 1:
        handleLogOut();
        break;
    case 2:
        handleCreateTask();
        break;
    case 3:
        handleEditTask();
        break;
    case 4:
        handleDeleteTask();
        break;
    case 5:
        handleViewTask();
        break;
    case 6:
        handleCreateEval();
        break;
    case 7:
        handleViewTAs();
        break;
    case 8:
        handleViewCourse();
        break;
    default:
        break;
    }
}
