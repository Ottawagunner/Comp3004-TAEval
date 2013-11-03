#include <QDebug>
#include "Controller.h"
#include "User.h"
#include "Instructor.h"
#include "Admin.h"
#include "TA.h"
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
    while(true){
        std::string buffer = (host.ReciveText());
        executeMessage(&buffer);
        host.SendText(buffer);
    }

    //w.show();
    //return a.exec();
}

void Controller::executeMessage(std::string *command)
{
    parse(command);
    handleMessage(command);
}

void Controller::parse(std::string *command) // userType, userName, actionRequested, Message
{
    short pos[4+1];

    for(short i = 0; i < 5; i++) // Goes through all '~' and records the positions in the string
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

    for(short i = 0; i < messageLength; i++){ // Assigns every segment of the command to the message array
        if(i == 0)
            message[i]=(*command).substr(pos[0],1);
        else
            message[i] = (*command).substr(pos[i-1]+1,pos[i]-pos[i-1]-1);
        //qDebug()<<(message[i].c_str());
    }
}

void Controller::handleMessage(std::string *command) // finds the userType which is one of A, I or T, created an object of the proper class and passes on the request
{
    short userType = 0;
    qDebug()<<"Made it to handle message";
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
        qDebug()<<"Made it through the switch";
            Instructor *i = new Instructor(&database);
            i->manageReq(message[2],message[3], command);
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
