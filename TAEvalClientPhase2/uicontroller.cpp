#include "uicontroller.h"

UIController::UIController(ClientControl *mainControl, int argc, char **argv)
    :a(argc, argv)
{
    control = mainControl;
}
int UIController::run(){
    d = new LoginDialog(this);
    d->show();
    a.exec();
    return 0;
}
/*
  * Member Function: loginNotify
  * Description: This function notifies the controller that there has been a request made
  *                 to log in. It makes a call to the general notification function in the
  *                 controller class.
  */
void UIController::loginNotify(){
    //Send info to main controller to verify
    std::string *returnInfo;
    d->getUserInfo(&username, &currUserType);
    control->giveRequest(username,currUserType,"LOGINREQUEST", "",returnInfo);
    //assume it is verified
    if(currUserType == "t"){
        t = new TAView(this);
        t->show();
        d->hide();
    }
    else{
        i = new InstructorView(this);
        i->show();
        d->hide();
        updateList("COMP3004");
        updateList("COMP2404");
        updateList("COMP2401");
    }

}
void UIController::updateList(std::string item){
    i->addToList(item);
}
void UIController::logoutNotify(){
    std::string *returnInfo;
    control->giveRequest(username,currUserType,"LOGOUTREQUEST", "",returnInfo);
    d->clearInfo();
    if(currUserType == "i"){
        i->hide();
        delete(i);
    }
    if(currUserType == "t"){
        t->hide();
        delete(t);
    }
    d->show();
}
void UIController::reqViewCourseList(std::string){
    qDebug("VIEW ALL COURSES REQ");
}

void UIController::reqViewTask(std::string taskID){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWONETASK",taskID,returnInfo);
}
void UIController::reqViewAllTasks(std::string addInfo){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWALLTASKS",addInfo,returnInfo);
}
void UIController::reqViewEval(std::string taskID){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWONEEVAL",taskID,returnInfo);
}

void UIController::reqViewAllEvals(){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWALLEVALS","",returnInfo);
}
void UIController::reqAddTask(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"ADDTASK",info,returnInfo);
}

void UIController::reqDeleteTask(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"DELETETASK",info,returnInfo);
}

void UIController::reqEditTask(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"EDITTASK",info,returnInfo);
}
void UIController::reqAddEval(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"ADDEVAL",info,returnInfo);
}
void UIController::reqDeleteEval(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"DELETEEVAL",info,returnInfo);
}
void UIController::reqEditEval(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"EDITEVAL",info,returnInfo);
}
void UIController::reqViewAllTAs(std::string addInfo){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWALLTAS",addInfo,returnInfo);
}
