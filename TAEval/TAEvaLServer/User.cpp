#include "User.h"


User::User(Database *d)
{
    database = d;
}

std::string User::getName()
{
    return name;
}

std::string User::getUserName()
{
    return userName;
}

std::string User::getEmail()
{
    return email;
}

std::string User::encode(short messageLength, std::string lockStatus, std::string message)
{
    std::stringstream mL;
    mL << messageLength;
    return ""+mL.str()+"~"+lockStatus+"~"+message;
}

std::string User::encode(short listLength, std::string* list)
{
    std::string encodedList = "";
    for(int i=0; i<listLength; i++)
    {
        encodedList+=list[i];
        if(i+1 < listLength)
            encodedList+="~";
    }
}

std::string User::encode(std::string original, std::string toAdd)
{
    return original+"~"+toAdd;
}
std::string* User::parser(std::string command) // numberOfTildas, message
 {
    std::cout <<"enter teh parser"<<std::endl;
    short firstPos = command.find_first_of("~", 0);
    std::string firstP = command.substr(0,firstPos);
    int numberOfSegments = atoi(firstP.c_str())+1;
    std::cout<<numberOfSegments<<std::endl;
    std::cout<<command<<std::endl;
    short pos[numberOfSegments];

     std::string* message = new std::string[numberOfSegments+1]; // Creates new array of string to contain the new message
     for(int i=0; i<numberOfSegments;i++)
         message[i] = "";

     //qDebug()<<"";
     qDebug()<<"Positions of ~:BLEHH";
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
         //qDebug()<<pos[i]; // note it won't show 0 as the continue skips this call
     }
     //qDebug()<<"";
     qDebug()<<"Content of BLEHH";

     for(short i = 0; i < numberOfSegments; i++) // Assigns every segment of the command to the message array
     {
         if(i == 0)
             message[i] = command.substr(pos[i],pos[i+1]-pos[i]);
         else if(i+1 >= numberOfSegments)
             message[i] = command.substr(pos[i]+1,-1);
         else
             message[i] = command.substr(pos[i]+1,pos[i+1]-pos[i]-1);
         qDebug()<<(message[i].c_str());
     }
     std::cout << "Finished with the parser" <<std::endl;
     return message;
 }
