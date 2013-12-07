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
    if(currUserType.compare("t")){
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
    if(currUserType.compare("i")){
        i->hide();
        delete(i);
    }
    if(currUserType.compare("t")){
        t->hide();
        delete(t);
    }
    d->show();
}
void UIController::reqViewCourseList(std::string){
    qDebug("VIEW ALL COURSES REQ");
}

void UIController::reqViewTask(std::string taskID){
    qDebug("VIEW ONE TASK REQ");
}
void UIController::reqViewAllTasks(){
    qDebug("VIEW ALL TASKs REQ");
}
void UIController::reqViewEval(std::string taskID){
    qDebug("VIEW ONE EVAL REQ");
}

void UIController::reqViewAllEvals(){
    qDebug("VIEW ALL EVALS REQ");
}
void UIController::reqAddTask(){
    qDebug("ADD TASK REQ");
}

void UIController::reqDeleteTask(){
    qDebug("DELETE TASK REQ");
}

void UIController::reqEditTask(){
    qDebug("EDIT TASK REQ");
}
void UIController::reqAddEval(){
    qDebug("ADD EVAL REQ");
}
void UIController::reqDeleteEval(){
    qDebug("DELETE EVAL REQ");
}
void UIController::reqEditEval(){
    qDebug("EDIT EVAL REQ");
}
void UIController::reqViewAllTAs(){
    qDebug("VIEW ALL TAs Req");
}
