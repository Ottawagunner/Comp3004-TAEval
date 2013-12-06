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
void UIController::loginNotify(std::string uname, char utype){
    //Send info to main controller to verify
    control->giveRequest(uname,utype,"LOGINREQUEST", "");
    //assume it is verified
    d->getUserInfo(&username, &currUserType);
    if(utype == 't'){
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
    d->clearInfo();
    if(currUserType == 'i'){
        i->hide();
        delete(i);
    }
    if(currUserType == 't'){
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
