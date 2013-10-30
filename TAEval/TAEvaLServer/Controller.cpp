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
    parse(&command);
    if(message[0].compare("I")==0){
        Instructor *t = new Instructor(&database);
        t->manageReq(message[2],message[3], &command);
        delete(t);
    }

}

void Controller::parse(std::string* command)
{

    int pos[4+1];

    for(int i = 0; i < 5; i++) // Goes through all '~' and records the positions in the string
    {
        pos[i] = 0;
        if(i == 0) continue;
        else
        {
            if(pos[i-1]+1 >= (*command).length())
            {
                pos[i] = -1;
                break;
            }
            pos[i] = (*command).find_first_of("~", pos[i-1]+1);
        }
    }
    message[0]=(*command).substr(pos[0],1);
    message[1]=(*command).substr(pos[0]+1,pos[1]-1);
    message[2]=(*command).substr(pos[1]+1,(pos[2]-pos[1]-1));
    message[3]=(*command).substr(pos[2]+1,pos[3]);

    qDebug()<<(message[0].c_str());
    qDebug()<<(message[1].c_str());
    qDebug()<<(message[2].c_str());
    qDebug()<<(message[3].c_str());

}
