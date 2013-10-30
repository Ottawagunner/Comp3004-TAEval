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

Controller::~Controller()
{
    delete &database;
}

void Controller::executeMessage(std::string command)
{
    parse(command);
    handleMessage();
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



    //for(short i = 0; i < message.)
    message[0]=command.substr(pos[0],1);
    message[1]=command.substr(pos[0]+1,pos[1]-1);
    message[2]=command.substr(pos[1]+1,(pos[2]-pos[1]-1));
    message[3]=command.substr(pos[2]+1,pos[3]);

    qDebug()<<(message[0].c_str());
    qDebug()<<(message[1].c_str());
    qDebug()<<(message[2].c_str());
    qDebug()<<(message[3].c_str());

}

void Controller::handleMessage() // finds the userType which is one of A, I or T, created an object of the proper class and passes on the request
{
    short userType = 0;

    if(message[0].compare("A") == 0) userType = 1;
    else if(message[0].compare("I") == 0) userType = 2;
    else if(message[0].compare("T") == 0) userType = 3;
    switch(userType){
        case 1:
        {
            Admin *a = new Admin(&database);
            //a->manageReq(message[2],message[3], &command);
            delete(a);
            break;
        }
        case 2:
        {
            Instructor *i = new Instructor(&database);
            //i->manageReq(message[2],message[3], &command);
            delete(i);
            break;
        }
        case 3:
        {
            TA *t = new TA(&database);
            //t->manageReq(message[2],message[3], &command);
            delete(t);
            break;
        }
        default:
            qDebug()<<"ERROR: User type not recognized.";
            break;
    }
}
