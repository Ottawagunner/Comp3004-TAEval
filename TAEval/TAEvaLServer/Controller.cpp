#include <QDebug>
#include "Controller.h"
#include "User.h"
#include "Instructor.h"
#include "Admin.h"
#include "TA.h"
#include "decoder.h"
#include <cstdlib>
#include <string>

using namespace std;

Controller::Controller(int size, std::string path, std::string* fileList) : database(size, path, fileList)
{
    for(int i=0; i<messageLength;i++)
        message[i] = "";
    //database = *(new Database(4,path, fileList));
}

Controller::~Controller()
{
    delete &database;
}

int Controller::runServer(){
    //QApplication a(argc, argv);
    //MainWindow w;
    host.Setup();
    while(true)
    {
        listening = true;
        do{
            std::string buffer = (host.ReciveText());
            executeMessage(&buffer);
            host.SendText(buffer);
        }while(listening);
        listen(host.server, 100);  // 50 (the backlog) isn't really used on modern systems
        host.clilen = sizeof(host.cliaddr);
        host.client = accept(host.server,(sockaddr*)&(host.servaddr), &(host.clilen));  // addr gets info about client
    }
    //w.show();
    //return a.exec();
}

void Controller::executeMessage(std::string *command)
{
    decoder decode = *new decoder();
    std::string* parsedCommand;

    decode.decode('~', *command, &parsedCommand);
    //for(int i=0; i<5;i++) std::cout<<parsedCommand[i]<<std::endl;
    handleMessage(parsedCommand, command);
}

void Controller::handleMessage(std::string *command, std::string* response) // finds the userType which is one of A, I or T, created an object of the proper class and passes on the request
{
    short userType = 0;
    for(int i=0; i<5;i++) std::cout<<command[i]<<std::endl;
    if(command[2].compare("a") == 0) userType = 1;
    else if(command[2].compare("i") == 0) userType = 2;
    else if(command[2].compare("t") == 0) userType = 3;
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

            i->manageReq(command[3],command[4], response);
            delete(i);
            if(command[3].compare("LogoutRequest")==0)
            {
                qDebug()<<"LOGOUT!!";
                listening=false;
            }
            break;
        }
        case 3:
        {
            TA *t = new TA(&database);
            //t->manageReq(command[2],command[3], &command);
            delete(t);
            break;
        }
        default:
            qDebug()<<"ERROR: User type not recognized.";
            break;
    }
}

