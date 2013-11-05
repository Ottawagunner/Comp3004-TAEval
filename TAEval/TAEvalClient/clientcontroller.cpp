#include "clientcontroller.h"
#include <QDebug>

clientcontroller::clientcontroller()
{
    userName = "Glynda Goodwitch";
    userType = "I";
    loggedIn = false;
}

int clientcontroller::run(int argc, char **argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    window = &w;
    w.show();
    w.setController(this);
    return a.exec();
}

short clientcontroller::handleRunButton(int index)
{
    std::string response ="";
    std::string message;
    switch(index)
    {
    case 0:
        client.Setup();
        response = encode("LoginRequest", userName);
        client.SendText(response);
        if(client.RecieveText().compare("1~U~Login successful")==0)
            window->writeToLog("Login Passed");
        else{
            window->writeToLog("Login Failed");
        }
        break;
    case 1:
        response = encode("LogoutRequest", userName);
        client.SendText(response);
        handleMessage(client.RecieveText());
        close(client.sockfd);
        window->writeToLog("Logout Passed");
        return 0;
        break;
    case 2:
        response = encode("CreateTaskRequest", "Please grade all of the tests in your mailbox");
        break;
    case 3:
        response = encode("EditTaskRequest", "2~Init-Ruby~Do Lab"); // WIP
        break;
    case 4:
        message = "InitBlake";
        response = encode("DeleteTaskRequest", message);
        client.SendText(response);
        if(client.RecieveText().compare("1~U~Delete task handled")==0)
            window->writeToLog("Delete Task Passed");
        else
            window->writeToLog("Delete Task Failed");
        break;
    case 5:
        response = encode("ViewTaskRequest", userName);
        break;
    case 6:
        response = encode("CreateEvaluationRequest", "3~InitRuby~5~Good Job");
        break;
    case 7:
        response = encode("ViewTARequest", "MNSTR101");
        client.SendText(response);
        if(client.RecieveText().compare("4~U~Ruby Rose~Weiss Schnee~Yang Xiao Long~Blake Belladonna")==0)
            window->writeToLog("View TAs Passed");
        else
            window->writeToLog("View TAs Failed");
        break;
    case 8:
        response = encode("ViewCoursesRequest", userName);
        client.SendText(response);
        if(client.RecieveText().compare("2~U~MNSTR101~HIST101")==0)
            window->writeToLog("View Courses Passed");
        else
            window->writeToLog("View Courses Failed");
        break;
    default:
        return 1;
        break;
    }

    //handleMessage(client.RecieveText());
    return 0;
}

std::string* clientcontroller::parse(std::string command, int numberOfSegments, bool log) // numberOfTildas, lockStatus, message
 {
     short pos[numberOfSegments];

     std::string* message = new std::string[numberOfSegments]; // Creates new array of string to contain the new message
     for(int i=0; i<numberOfSegments;i++)
         message[i] = "";

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
     }

     for(short i = 0; i < numberOfSegments; i++) // Assigns every segment of the command to the message array
     {
         if(i == 0)
             message[i] = command.substr(pos[i],pos[i+1]-pos[i]);
         else if(i+1 >= numberOfSegments)
             message[i] = command.substr(pos[i]+1,-1);
         else
             message[i] = command.substr(pos[i]+1,pos[i+1]-pos[i]-1);
         if(log && message[i].length()>=2) window->writeToLog(QString::fromStdString(message[i]));
     }
     return message;
 }

std::string* clientcontroller::handleMessage(std::string command) // Learns if data server-side is locked or not and decomposes the message
 {
     std::string* parsedCommand = parse(command, 3, false); // Parses the command and turns message[] into {numberOfTildas,lockStatus,message}

     bool locked = true; // check if data is locked

     if(parsedCommand[1].compare("L") == 0){
         locked = true;
     }
     else if(parsedCommand[1].compare("U") == 0){
         locked = false;
     }
     else
     {
         qDebug()<<"Data is corrupted.";
     }

     int numberOfSegments = atoi(parsedCommand[0].c_str()); // knows how many tildas the last part of the message contains

     std::string* message = parse(parsedCommand[2], numberOfSegments, true); // parses it
     return message;

     // do stuff with the message;
     //qDebug()<<"";
 }

std::string clientcontroller::encode(std::string command, std::string userInput)
{
    return userType+"~"+userName+"~"+command+"~"+userInput;
}
