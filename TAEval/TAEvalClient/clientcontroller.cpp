#include "clientcontroller.h"
#include <QDebug>
#include <iostream>

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
    encoder e;
    response = e.encode(userType, userName);
    short tildaInResponse = 2;

    switch(index)
    {
    case 0:
        client.Setup();
        response = e.encode(response, "LoginRequest");
        tildaInResponse++;
        response = e.encode(response, userName);
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        client.SendText(response);
        if(client.RecieveText().compare("2~U~Login successful")==0)
            window->writeToLog("Login Passed");
        else{
            window->writeToLog("Login Failed");
        }
        break;
    case 1:
        response = e.encode(response, "LogoutRequest");
        tildaInResponse++;
        response = e.encode(response, userName);
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        handleMessage(client.RecieveText());
        close(client.sockfd);
        window->writeToLog("Logout Passed");
        return 0;
        break;
    case 2:
        response = e.encode(response, "CreateTaskRequest");
        tildaInResponse++;
        response = e.encode(response, "Please grade all of the tests in your mailbox");
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        //client.SendText(response);
        break;
    case 3:
        response = e.encode(response, "EditTaskRequest");
        tildaInResponse++;
        response = e.encode(response, "2~Init-Ruby~Do Lab");
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        //client.SendText(response);
        break;
    case 4:
        message = "InitBlake";
        response = e.encode(response, "DeleteTaskRequest");
        tildaInResponse++;
        response = e.encode(response, message);
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        client.SendText(response);
        if(client.RecieveText().compare("2~U~Delete task handled")==0)
            window->writeToLog("Delete Task Passed");
        else
            window->writeToLog("Delete Task Failed");
        break;
    case 5:
        response = e.encode(response, "ViewTaskRequest");
        tildaInResponse++;
        response = e.encode(response, userName);
        tildaInResponse++;
        //client.SendText(response);
        break;
    case 6:
        response = e.encode(response, "CreateEvaluationRequest");
        tildaInResponse++;
        response = e.encode(response, "3~InitRuby~5~Good Job");
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        //client.SendText(response);
        break;
    case 7:
        response = e.encode(response, "ViewTARequest");
        tildaInResponse++;
        response = e.encode(response, "MNSTR101");
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        client.SendText(response);
        if(client.RecieveText().compare("5~U~Ruby Rose~Weiss Schnee~Yang Xiao Long~Blake Belladonna")==0)
            window->writeToLog("View TAs Passed");
        else
            window->writeToLog("View TAs Failed");
        break;
    case 8:
        response = e.encode(response, "ViewCoursesRequest");
        tildaInResponse++;
        response = e.encode(response, userName);
        tildaInResponse++;
        response = e.encode(tildaInResponse, response);
        client.SendText(response);
        if(client.RecieveText().compare("3~U~MNSTR101~HIST101")==0)
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

std::string* clientcontroller::handleMessage(std::string command) // Learns if data server-side is locked or not and decomposes the message
{
     std::cout<<"handleMessage: "<<command<<std::endl;
     std::string* parsedCommand;
     decoder decode = *new decoder();
     decode.decode('~',command, &parsedCommand); // Parses the command and turns message[] into {numberOfTildas,lockStatus,message}

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
     std::string* message;
     if(parsedCommand[2].compare(userName) == 0){
        decode.decode('~',parsedCommand[3], &message); // parses it
     }
     else
         decode.decode('~',parsedCommand[2], &message); // parses it
     for(int i=0; i<3;i++) std::cout<<message[i]<<std::endl;

     return message;

     // do stuff with the message;
     //qDebug()<<"";
}

