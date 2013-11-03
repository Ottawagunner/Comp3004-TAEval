#include "Instructor.h"
#include "QDebug"

Instructor::Instructor(Database *database):User(database){
    reqType[0] = "LoginRequest";
    reqType[1] = "LogoutRequest";
    reqType[2] = "CreateTaskRequest";
    reqType[3] = "DeleteTaskRequest";
    reqType[4] = "EditTaskRequest";
    reqType[5] = "ViewTaskRequest";
    reqType[6] = "ViewTARequest";
    reqType[7] = "ViewCourseRequest";
    reqType[8] = "CreateEvaluationRequest";

}
void Instructor::search(std::string s, std::string a[]){

}
short Instructor::createTask(std::string message, std::string* response){
    qDebug()<<"createTaskHandler";
    *response = "Create Task handled";
    return 0;
}
short Instructor::editTask(std::string message, std::string* response){
    qDebug()<<"editTaskHandler";
    *response = "Edit task handled";
    return 0;
}
short Instructor::deleteTask(std::string message, std::string* response){
    qDebug()<<"deleteTaskHandler";
    return 0;
}
short Instructor::viewTask(std::string message, std::string* response){
    qDebug()<<"viewTaskHandler";
    return 0;
}
short Instructor::viewTAs(std::string message, std::string* response){
    qDebug()<<"viewTAHandler";
    return 0;
}
short Instructor::viewCourses(std::string message, std::string* response){
    qDebug()<<"viewCourseHandler";
    return 0;
}
short Instructor::writeReview(std::string message, std::string* response){
    qDebug()<<"writeReviewHandler";
    return 0;
}
void Instructor::manageReq(std::string req, std::string message, std::string *response){
    int reqNum=-1;
    for(int i = 0; i<9; i++){
        if(req.compare(reqType[i])==0){
            reqNum = i;
            break;
        }
    }
    switch(reqNum){
    case 0:
        login(message, response);
        break;
    case 1:
        logout(message,response);
        break;
    case 2:
        createTask(message, response);
        break;
    case 3:
        deleteTask(message,response);
        break;
    case 4:
        editTask(message,response);
        break;
    case 5:
        viewTask(message,response);
        break;
    case 6:
        viewTAs(message,response);
        break;
    case 7:
        viewCourses(message,response);
        break;
    case 8:
        writeReview(message,response);
        break;
    default:
        *response = "ERROR";
        break;
}

}
