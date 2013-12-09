#include "uicontroller.h"
#include <QDebug>

UIController::UIController(ClientControl *mainControl, int argc, char **argv)
    :a(argc, argv)
{
    control = mainControl;
}
std::string UIController::getUser(){
    return username;
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
    std::string *returnInfo;
    d->getUserInfo(&username, &currUserType);
    control->giveRequest(username,currUserType,"LOGIN", "",&returnInfo);

    //for(int i=0; i<2;i++) std::cout<< "randomness: "<<returnInfo[i]<<std::endl;

    std::stringstream convert(returnInfo[0]);
    int size;
    convert>>size;
    size++;
    if(returnInfo[1].compare("FAILURE")!=0){
        if(currUserType.compare("t")==0){
            t = new TAView(this);
            t->show();
            d->hide();
            for(int i=1; i<size; i++)
                updateTaskList(returnInfo[i]);
        }
        else{
            i = new InstructorView(this);
            i->show();
            d->hide();
            for(int i=1; i<size; i++)
                updateCourseList(returnInfo[i]);
        }
    }
    else{
        //Notify login dialog
    }
}

void UIController::logoutNotify(){
    std::string *returnInfo;
    control->giveRequest(username,currUserType,"LOGOUT", "",&returnInfo);
    d->clearInfo();
    if(currUserType.compare("i")==0){
        i->hide();
        delete(i);
    }
    if(currUserType.compare("t")==0){
        t->hide();
        delete(t);
    }
    d->show();
}

void UIController::reqViewTask(std::string taskID){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWONETASK",taskID,&returnInfo);
    updateIDialog(returnInfo[1],returnInfo[2]);
}
void UIController::reqViewAllTasks(std::string addInfo){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWALLTASKS",addInfo,&returnInfo);
    std::stringstream convert(returnInfo[0]);
    int size;
    convert>>size;
    for(int i=1; i<size; i++){
        updateListDialogList(returnInfo[i]);
    }
}
void UIController::reqViewEval(std::string taskID){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWONEEVAL",taskID,&returnInfo);
    updateIDialog(returnInfo[1],returnInfo[2]);
}

void UIController::reqViewAllEvals(){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWALLEVALS","",&returnInfo);
    std::stringstream convert(returnInfo[0]);
    int size;
    convert>>size;
    for(int i=1; i<size; i++){
        updateListDialogList(returnInfo[i]);
    }
}
void UIController::reqAddTask(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"ADDTASK",info,&returnInfo);
    updateIDialog("YOU","BITCH");
}

void UIController::reqDeleteTask(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"DELETETASK",info,&returnInfo);
}

void UIController::reqEditTask(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"EDITTASK",info,&returnInfo);
    updateIDialog("YOU","BITCH");
}
void UIController::reqAddEval(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"ADDEVAL",info,&returnInfo);
    updateIDialog("YOU","BITCH");
}
void UIController::reqDeleteEval(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"DELETEEVAL",info,&returnInfo);
}
void UIController::reqEditEval(std::string info){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"EDITEVAL",info,&returnInfo);
    updateIDialog("YOU","BITCH");
}
void UIController::reqViewAllTAs(std::string addInfo){
    std::string *returnInfo;
    control->giveRequest(username, currUserType,"VIEWALLTAS",addInfo,&returnInfo);
    std::stringstream convert(returnInfo[0]);
    int size;
    convert>>size;
    for(int i=1; i<size; i++){
        updateListDialogList(returnInfo[i]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
/*******************UPDATE FUNCTIONS************************************************/
/////////////////////////////////////////////////////////////////////////////////////

void UIController::updateCourseList(std::string item){
    i->addToList(item);
}
void UIController::updateTaskList(std::string item){
    t->addToTaskList(item);
}

void UIController::updateListDialogList(std::string s){
    /*if(currUserType.compare("t")==0){
        ViewListDialog *v;
        t->getListDialog(&v);
        v->updateList(s);
    }
    else{*/
        ViewListDialog *v;
        i->getListDialog(&v);
        v->updateList(s);
    //}
}
void UIController::updateIDialog(std::string s1, std::string s2){
    if(currUserType.compare("t")==0){
        ViewIndividualDialog *id;
        t->getIndDialog(&id);
        id->updateInfo(s1,s2);
    }
    else{
        ViewListDialog *v;
        ViewIndividualDialog *id;
        i->getListDialog(&v);
        v->getIndivDialog(&id);
        id->updateInfo(s1,s2);
    }
}
