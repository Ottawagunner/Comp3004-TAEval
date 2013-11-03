#include "clientcontroller.h"
#include <QDebug>

clientcontroller::clientcontroller(){
    userName = "JohnSmith";
}

int clientcontroller::run(int argc, char **argv){
    QApplication a(argc, argv);
    MainWindow w;
    window = &w;
    w.show();
    w.setController(this);
    return a.exec();
}
short clientcontroller::handleLogIn(){
    QString s ="Logging in username:";//+userName);
    window->writeToLog(s);
    client.Setup();
    client.SendText("I"+userName+"~LoginRequest~"+userName);
    s = "Request Sent";
    window->writeToLog(s);
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleLogOut(){
    client.SendText("I"+userName+"~LogoutRequest~"+userName);
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleCreateTask(){
    std::string taskInfo;
    taskInfo = "Please grade all of the tests in your mailbox";
    client.SendText("I"+userName+"~CreateTaskRequest~"+taskInfo);
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleEditTask(){
    QString s = "Edit Task Test Handled";
    window->writeToLog(s);
    return 0;//unsure of how this is going to work but its here until we figure it out
}
short clientcontroller::handleDeleteTask(){
    client.SendText("I"+userName+"~DeleteTaskRequest~"+"TASK001");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleViewTask(){
    client.SendText("I"+userName+"~ViewTaskRequest~"+"COMP3004");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleCreateEval(){
    client.SendText("I"+userName+"~CreateEvaluationRequest~"+"TASK001");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleViewTAs(){
    client.SendText("I"+userName+"~ViewTARequest~"+"COMP3004");
    QString buffer = QString::fromStdString(client.ReciveText());
    window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleViewCourse(){
    client.SendText("I"+userName+"~ViewCoursesRequest~"+userName);
    QString buffer = QString::fromStdString(client.ReciveText());
   window->writeToLog(buffer);
    return 0;
}
short clientcontroller::handleRunButton(int index){
    switch(index){
    case 0:
        handleLogIn();
        break;
    case 1:
        handleLogOut();
        break;
    case 2:
        handleCreateTask();
        break;
    case 3:
        handleEditTask();
        break;
    case 4:
        handleDeleteTask();
        break;
    case 5:
        handleViewTask();
        break;
    case 6:
        handleCreateEval();
        break;
    case 7:
        handleViewTAs();
        break;
    case 8:
        handleViewCourse();
        break;
    default:
        break;
    }
}
std::string* clientcontroller::parse(std::string command, int numberOfSegments) // numberOfTildas, lockStatus, message
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

void clientcontroller::handleMessage(std::string command) // Learns if data server-side is locked or not and decomposes the message
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
