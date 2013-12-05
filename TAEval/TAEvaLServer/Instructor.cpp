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
    std::string *messageArray;

    std::string** coursestemp;
    std::string** tastemp;
    std::string** tasktemp;
    std::string out = "";
    int cn, tn, kn, tt;
    int count = 0;

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
             std::cout<<"case0"<<std::endl;
            *response = *new std::string(encode(2, "U", "Login successful"));
            break;
        }
        *response = encode(2,"U", "Invalid Login");
        break;
    case 1:
        *response = encode(2, "U", "Logout successful");
        break;
    case 2:
         *response = encode(2, "U", "Create Task handled");
        break;
    case 3:
        std::cout<<message<<std::endl;
         if(!database->removeEntry(4,&message))
            *response = encode(2, "U", "Delete task handled");
         else{
             *response = encode(2, "U", "Delete Task Error");
         }

        break;
    case 4:
        {
            //setting up a edit task.
            //needs to parse through the message, to create the object and where to add it to.

            decoder decode = *new decoder();
            decode.decode('~',message, &messageArray);
            std::cout << messageArray[0]<<" asdhfadfasdfa" << std::endl;
            std::cout << messageArray[1]<<" asdhfadsfasdfa" << std::endl;
            std::cout << messageArray[2]<<" asdhfadffasdfa" << std::endl;
            std::cout << messageArray[3]<<" asdhfadfdasdfa" << std::endl;
            std::cout << messageArray[4]<<" asdhfadfaaaasdfa" << std::endl;
            temp = (database->query(4,&messageArray[1]));
            temp[1][0]=(messageArray[2]);
            temp[2][0]=(messageArray[3]);
            temp[3][0]=(messageArray[4]);

            database->edit(4,&messageArray[1],temp);

            *response = encode(2, "U", "edited the ");
            break;
        }
    case 5:
    {


           temp = (database->query(1,&message));

           if (temp == NULL){
               *response = "ERROR";
            }else {



           std::stringstream (temp[0][1]) >> cn;
           for (int i = 0; i < cn; i++){
               coursestemp = database->query(3, &temp[2][i]);
               std::cout << coursestemp[2][0]<<std::endl;
               std::stringstream (coursestemp[0][2]) >> tn;
               for (int k = 0; k < tn; k++){
                   tastemp = database->query(2, &coursestemp[2][k]);
                   std::cout <<tastemp[2][0]<<std::endl;
                   std::stringstream (tastemp[0][2]) >> kn;
                   for (int j = 0; j < kn; j++){
                       tasktemp = database->query(4, &tastemp[2][j]);
                       std::stringstream (tasktemp[0][1]) >> tt;
                       for (int h = 0; h < tt; h++){
                           out += *(new std::string(tasktemp[1][0])) + "~";
                           count++;
                       }
                   }
               }
           }

           *response = encode(count, "U", out);
           }
    }
           /*
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
                               out += encode(atoi(tasktemp[0][t].c_str()),tasktemp[t]);
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
    }*/
           break;
    case 6:
        qDebug()<<"MADE IT TO CASE 6";
        qDebug(message.c_str());
        temp = (database->query(3,&message));
        qDebug()<<"MADE IT PAST QUERY";
        std::stringstream (temp[0][2])>>num;
        std::cout<<num<<std::endl;
        for(int i=0; i<num;i++){
            encMessage.append(temp[2][i]);
            if((i != i+1)&&(i+1 !=num))
                encMessage.append("~");
        }
        *response = encode(num,"U", encMessage);
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
        {
            //setting up a new reveiw.
            //needs to parse through the message, to create the object and where to add it to.
            std::string *messageArray;
            decoder decode = *new decoder();
            decode.decode('~',message, &messageArray);
            std::cout << messageArray[1] << " asdfasdfasdfasdfa" <<std::endl;
            temp = (database->query(4,&messageArray[1]));
            temp[1][0]=(messageArray[2]);
            temp[2][0]=(messageArray[3]);
            temp[3][0]=(messageArray[4]);

            database->edit(4,&messageArray[1],temp);

            *response = encode(2, "U", "Write review handled");
            break;
        }
    default:
        *response = "ERROR";
        break;
}

}
