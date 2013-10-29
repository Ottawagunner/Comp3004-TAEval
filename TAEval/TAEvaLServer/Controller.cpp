#include <QDebug>
#include "Controller.h"
#include "User.h"
#include "Instructor.h"
#include "Admin.h"
#include "TA.h"

Controller::Controller()
{
    for(int i=0; i<message.size();i++)
        message[i] = "";
}

void Controller::executeMessage(std::string command)
{
    parse(command);
    //Add more commands
}

void Controller::parse(std::string command)
{
    int pos[message.size()+1];

    for(int i = 0; i < pos.size(); i++) // Goes through all '~' and records the positions in the string
    {
        pos[i] = 0;
        if(i == 0) continue;
        else
        {
            if(pos[i-1]+1 >= command.length)
            {
                pos[i] = -1;
                break;
            }
            pos[i] = command.find_first_of("~", pos[i-1]+1);
        }
    }

    for(int i = 0; i < pos.size()-1; i++)
    {
        message[i] = command.substr(pos[i],pos[i+1]);
    }
}
