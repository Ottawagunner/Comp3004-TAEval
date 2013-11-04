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
    reqType[7] = "ViewCoursesRequest";
    reqType[8] = "CreateEvaluationRequest";

}

void Instructor::search(std::string s, std::string a[]){

}

void Instructor::manageReq(std::string req, std::string message, std::string *response){
    int reqNum=-1;
    std::string** temp;
    for(int i = 0; i<9; i++){
        if(req.compare(reqType[i])==0){
            reqNum = i;
            break;
        }
    }
    switch(reqNum){
    case 0:
        temp = (database->query(1,&message));
        if((temp) != NULL){
            *response = encode(1, "U", "Login successful");
            break;
        }
        *response = "Invalid Login";
        break;
    case 1:
        *response = encode(1, "U", "Logout successful");
        break;
    case 2:
         *response = encode(1, "U", "Create Task handled");
        break;
    case 3:
        *response = encode(1, "U", "Delete task handled");
        break;
    case 4:
        *response = encode(1, "U", "Edit task handled");
        break;
    case 5:
        *response = encode(4, "U", "Mark midterms~4/5~All midterms marked two days later than expected~View task handled");
        break;
    case 6:
        *response = encode(4, "U", "Alphonse Brown~Charles Dupont~Elise Festive~View TAs handled");
        break;
    case 7:
        *response = encode(6, "U", "COMP1804~COMP2804~COMP3804~COMP4804~COMP3004~View courses handled");
        break;
    case 8:
        *response = encode(1, "U", "Write review handled");
        break;
    default:
        *response = "ERROR";
        break;
}

}
