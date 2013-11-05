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
    int num=-1;
    std::string encMessage="";
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
        *response = encode(1,"U", "Invalid Login");
        break;
    case 1:
        *response = encode(1, "U", "Logout successful");
        break;
    case 2:
         *response = encode(1, "U", "Create Task handled");
        break;
    case 3:
        //database->removeEntry(4,&message);
        *response = encode(1, "U", "Delete task handled");

        break;
    case 4:
        *response = encode(1, "U", "Edit task handled");
        break;
    case 5:
    {
           std::string** coursestemp;
           std::string** tastemp;
           std::string** tasktemp;
           std::string out = "";
           int totsize = 0;

           temp = (database->query(1,&message));                       //Username
           if((temp) != NULL)
           {
               int numins,numcor,numta;

               std::stringstream (temp[0][1]) >> numins;
               for (int k = 0; k < numins; k++)
               {
                   coursestemp = (database->query(3,&temp[1][k]));          // every course by username

                   std::stringstream (coursestemp[0][2]) >> numcor;
                   for(int j=1;j<numcor;j++)
                   {
                       tastemp = (database->query(2,&coursestemp[2][j]));   // every ta by course

                       std::stringstream (tastemp[0][2]) >> numta;
                       for(int h=1;h<numta;h++)
                       {
                           tasktemp = (database->query(2,&tastemp[2][h]));// every task by ta
                           for (int t=1;t< atoi(tasktemp[0][0].c_str());t++)
                           {
                               totsize += atoi(tasktemp[0][0].c_str());
                               out = encode(atoi(tasktemp[0][t].c_str()),tasktemp[t]);
                           }
                        out += "\n";
                       }
                   }
               }
               *response = encode(totsize, "U", out);
               break;
           }
        *response = "Error";
        break;
    }
    case 6:
        *response = encode(4, "U", "Alphonse Brown~Charles Dupont~Elise Festive~View TAs handled");
        break;
    case 7:
        temp = (database->query(1,&message));
        std::stringstream (temp[0][1])>>num;
        for(int i=0; i<num;i++){
            encMessage.append(temp[1][i]);
            if((i != i+1)&&(i+1 !=num))
                encMessage.append("~");
        }
        *response = encode(num,"U", encMessage);
        break;
    case 8:
        *response = encode(1, "U", "Write review handled");
        break;
    default:
        *response = "ERROR";
        break;
}

}
