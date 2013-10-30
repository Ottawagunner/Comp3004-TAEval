#include <QDebug>
#include "Controller.h"
#include "User.h"
#include "Instructor.h"
#include "Admin.h"
#include "TA.h"
#include <cstdlib>
#include <string>

using namespace std;

Controller::Controller()
{
    for(int i=0; i<4;i++)
        message[i] = "";
    Database* database = new Database(); //Need to add parameters
}

void Controller::executeMessage(std::string command)
{
    bool isAdmin = false;
    bool isInstructor = false;
    bool isTA = false;
    bool userExists = false;

    parse(command);
    if(message[0].compare("I")==0){
        Instructor *t = new Instructor(&database);
        t->manageReq(message[2],message[3], &command);
        delete(t);
    }

    short userType = userType(message[0]);
    switch(userType){
        case 0:
            qDebug()<<"ERROR: User type not recognized.";
            break;
        case 1:
            isAdmin = true;
            break;
        case 2:
            isInstructor = true;
            break;
        case 3:
            isTA = true;
            break;
        default:
            qDebug()<<"ERROR: User type not parsed.";
            break;
    }


    //Add more commands
}

void Controller::parse(std::string command) // userType, userName, actionRequested, Message
{

   /* int index=1;
    int pos[5];
    short currPos = 0;
    pos[currPos] = 0;
    currPos=currPos+1;
    while(command[index] != NULL){ // This should work if you turned command from string to char[]
        if(command[index] == '~'){
            pos[currPos] = index;
            currPos=currPos+1;
            qDebug(command[index]);
        }
        ++index;
    }*/
    short pos[4+1];

    for(short i = 0; i < 5; i++) // Goes through all '~' and records the positions in the string
    {
        pos[i] = 0;
        if(i == 0) continue;
        else
        {
            if(pos[i-1]+1 >= command.length())
            {
                pos[i] = -1;
                break;
            }
            pos[i] = command.find_first_of("~", pos[i-1]+1);
        }
    }
    message[0]=command.substr(pos[0],1);
    message[1]=command.substr(pos[0]+1,pos[1]-1);
    message[2]=command.substr(pos[1]+1,(pos[2]-pos[1]-1));
    message[3]=command.substr(pos[2]+1,pos[3]);

    qDebug()<<(message[0].c_str());
    qDebug()<<(message[1].c_str());
    qDebug()<<(message[2].c_str());
    qDebug()<<(message[3].c_str());

}

short Controller::userType(std::string userType) // userType is either A, I or T and returns 1, 2 or 3 respectively
{
    if(userType.compare("A") == 0) return 1;
    else if(userType.compare("I") == 0) return 2;
    else if(userType.compare("T") == 0) return 3;
    else return 0;
}
