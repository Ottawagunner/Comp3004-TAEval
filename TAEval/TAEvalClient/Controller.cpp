#include <QDebug>
#include <cstdlib>
#include <string>
#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

std::string* Controller::parse(std::string command, int numberOfSegments) // numberOfTildas, lockStatus, message
{
    short pos[numberOfSegments];

    std::string* message = new std::string[numberOfSegments]; // Creates new array of string to contain the new message
    for(int i=0; i<numberOfSegments;i++)
        message[i] = "";

    qDebug()<<"";
    qDebug()<<"Positions of ~:";
    for(short i = 0; i < numberOfSegments; i++) // Goes through numberOfSegments of '~' and records the positions in the string
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
        qDebug()<<pos[i]; // note it won't show 0 as the continue skips this call
    }
    qDebug()<<"";
    qDebug()<<"Content of message:";

    for(short i = 0; i < numberOfSegments; i++){ // Assigns every segment of the command to the message array
        if(i == 0)
            message[i] = command.substr(pos[i],pos[i+1]-pos[i]);
        else if(i+1 >= numberOfSegments)
            message[i] = command.substr(pos[i]+1,-1);
        else
            message[i] = command.substr(pos[i]+1,pos[i+1]-pos[i]-1);
        qDebug()<<(message[i].c_str());
    }

    return message;
}

void Controller::handleMessage(std::string command) // Learns if data server-side is locked or not and decomposes the message
{
    std::string* parsedCommand = parse(command, 3); // Parses the command and turns message[] into {numberOfTildas,lockStatus,message}
    qDebug()<<"";

    bool locked = true; // check if data is locked

    if(parsedCommand[1].compare("L") == 0){
        locked = true;
        qDebug()<<"Data is Locked";
        // do stuff here or later on
    }
    else if(parsedCommand[1].compare("U") == 0){
        locked = false;
        qDebug()<<"Data is Unlocked";
        // do stuff here or later on
    }
    else
    {
        qDebug()<<"Data is corrupted.";
    }

    int numberOfSegments = atoi(parsedCommand[0].c_str()); // knows how many tildas the last part of the message contains

    std::string* message = parse(parsedCommand[2], numberOfSegments); // parses it
    /*
     * I failed at liberating occupied memory => Memory Leak!
     */

    //for(int i=0; i<3;i++) // Deallocate the previous message from memory
    //    delete[] &(parsedCommand[i]);
    //delete parsedCommand;

    //for(int i=0; i<numberOfSegments;i++) // Deallocate the previous message from memory
    //     delete[] &(message[i]);
    //delete &message;


    // do stuff with the message;
    qDebug()<<"";
}
