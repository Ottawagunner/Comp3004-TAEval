#include <QDebug>
#include "Controller.h"
#include "User.h"
#include "Instructor.h"
#include "Admin.h"
#include "TA.h"

Controller::Controller()
{
    for(int i=0; i<4;i++)
        message[i] = "";
}

void Controller::executeMessage(std::string command)
{
    parse(command);
    //if(message[0])
    //Add more commands
}

void Controller::parse(std::string command)
{

   /* int index=1;
    int pos[5];
    short currPos = 0;
    pos[currPos] = 0;
    currPos=currPos+1;
    while(command[index] != NULL){
        if(command[index] == '~'){
            pos[currPos] = index;
            currPos=currPos+1;
            qDebug(command[index]);
        }
        ++index;
    }*/
    int pos[4+1];

    for(int i = 0; i < 5; i++) // Goes through all '~' and records the positions in the string
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

    for(int i = 0; i < 5-1; i++)
    {
        message[i] = command.substr(pos[i],pos[i+1]);
        //QString buffer = QString::fromStdString(message[i]);
        qDebug(message[i].c_str());
    }
}
