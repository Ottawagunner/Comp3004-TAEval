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
    for(int i=0; i<5;i++) std::cout<<command[i]<<std::endl;

    // send the message to the database
    //std::string* result;// string obtained from the db
    if(command[3].compare("LOGINREQUEST")==0)
    {
        std::string result[3][1]= {{"1"}, {"1"}, {"HIST1001"}};
        encoder e;
        std::string output = "";
        short tildaInRequest = 0;

        for(int i = 1; i < atoi(result[0][0].c_str()) +1 ; i++)
        {
            for(int j = 0; j < atoi(result[i][0].c_str()) ; j++)
            {
                output = e.encode(output, result[atoi(result[0][0].c_str())+ i][j]);
                tildaInRequest++;
            }
        }
        output = output.substr(1, -1); // removes the first tilda as it is going to be added again on the next line
        output = e.encode(tildaInRequest, output);
        *response = output;
    }
    else if(command[3].compare("LOGOUTREQUEST")==0)
    {
        std::string result[3][2]= {{"1",""}, {"2",""}, {"Ruby Rose", "Nora Valkyrie"}};
        encoder e;
        std::string output = "";
        short tildaInRequest = 0;

        for(int i = 1; i < atoi(result[0][0].c_str()) +1 ; i++)
        {
            for(int j = 0; j < atoi(result[i][0].c_str()) ; j++)
            {
                output = e.encode(output, result[atoi(result[0][0].c_str())+ i][j]);
                tildaInRequest++;
            }
        }
        output = output.substr(1, -1); // removes the first tilda as it is going to be added again on the next line
        output = e.encode(tildaInRequest, output);
        *response = output;
    }
    else if(command[3].compare("VIEWONETASK")==0)
    {
        std::string result[3][2]= {{"1",""}, {"2",""}, {"Title of Task 1", "Description of Task1"}};
        encoder e;
        std::string output = "";
        short tildaInRequest = 0;

        for(int i = 1; i < atoi(result[0][0].c_str()) +1 ; i++)
        {
            for(int j = 0; j < atoi(result[i][0].c_str()) ; j++)
            {
                output = e.encode(output, result[atoi(result[0][0].c_str())+ i][j]);
                tildaInRequest++;
            }
        }
        output = output.substr(1, -1); // removes the first tilda as it is going to be added again on the next line
        output = e.encode(tildaInRequest, output);
        *response = output;
    }
    else if(command[3].compare("VIEWALLTASKS")==0)
    {
        std::string result[3][3]= {{"1",""}, {"3",""}, {"T-1", "T-2", "T-3"}};
        encoder e;
        std::string output = "";
        short tildaInRequest = 0;
        for(int i = 1; i < atoi(result[0][0].c_str()) +1 ; i++)
        {
            for(int j = 0; j < atoi(result[i][0].c_str()) ; j++)
            {
                output = e.encode(output, result[atoi(result[0][0].c_str())+ i][j]);
                tildaInRequest++;
            }
        }
        output = output.substr(1, -1); // removes the first tilda as it is going to be added again on the next line
        output = e.encode(tildaInRequest, output);
        *response = output;
    }
    else if(command[3].compare("VIEWONEEVAL")==0)
    {

    }
    else if(command[3].compare("VIEWALLEVALS")==0)
    {

    }
    else if(command[3].compare("ADDTASK")==0)
    {

    }
    else if(command[3].compare("DELETETASK")==0)
    {

    }
    else if(command[3].compare("EDITTASK")==0)
    {

    }
    else if(command[3].compare("ADDEVAL")==0)
    {

    }
    else if(command[3].compare("DELETEEVAL")==0)
    {

    }
    else if(command[3].compare("EDITEVAL")==0)
    {

    }
    else if(command[3].compare("VIEWALLTAS")==0)
    {

    }
    else
    {
        std::string result[3][1]= {{"1"}, {"1"}, {"ERROR!!"}};
        encoder e;
        std::string output = "";
        short tildaInRequest = 0;

        // Loops through something like this
        //std::string output[5][3]= {{"2",""}, {"2",""}, {"3",""}, {"Title of Task 1", "Description of Task1 like he's good"}, {"Alpha", "Beta", "Gamma"}};
        //                           [0][0]   [1][0]     [2][0]       [3][0]                   [3][1]                           [4][0]   [4][1]  [4][2]

        for(int i = 1; i < atoi(result[0][0].c_str()) +1 ; i++)
        {
            for(int j = 0; j < atoi(result[i][0].c_str()) ; j++)
            {
                output = e.encode(output, result[atoi(result[0][0].c_str())+ i][j]);
                tildaInRequest++;
            }
        }
        output = output.substr(1, -1); // removes the first tilda as it is going to be added again on the next line
        output = e.encode(tildaInRequest, output);
        *response = output;
    }


    /* Encoding function once db works
    encoder e;
    std::string output = "";
    short tildaInRequest = 0;

    // Loops through something like this
    //std::string output[5][3]= {{"2",""}, {"2",""}, {"3",""}, {"Title of Task 1", "Description of Task1 like he's good"}, {"Alpha", "Beta", "Gamma"}};
    //                           [0][0]   [1][0]     [2][0]       [3][0]                   [3][1]                           [4][0]   [4][1]  [4][2]

    for(int i = 1; i < atoi(result[0][0].c_str()) +1 ; i++)
    {
        for(int j = 0; j < atoi(result[i][0].c_str()) ; j++)
        {
            output = e.encode(output, result[atoi(result[0][0].c_str())+ i][j]);
            tildaInRequest++;
        }
    }
    output = output.substr(1, -1); // removes the first tilda as it is going to be added again on the next line
    output = e.encode(tildaInRequest, output);
    *response = output;


    */

    /*
    short userType = 0;
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
    */
}

