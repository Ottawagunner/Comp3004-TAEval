#include "clientcontrol.h"
#include <QDebug>
#include <string>

ClientControl::ClientControl(int argc, char **argv)
{
    ui = new UIController(this, argc, argv);
}

int ClientControl::run(){
    connected = false;
    ui->run();
    return 0;
}
void ClientControl::giveRequest(std::string uname, std::string uType, std::string reqType,
                                std::string additionalInfo, std::string** returnInfo){

    //Checks all 3 necessary arguments to make sure all of them are well-defined
    if(uname.empty())
    {
        qDebug()<<"uname in giveRequest is empty";
        return;
    }
    if(reqType.empty())
    {
        qDebug()<<"reqType in giveRequest is empty";
        return;
    }
    if(!(uType.compare("t") == 0 || uType.compare("i") == 0))
    {
        qDebug()<<"uType in giveRequest is not valid";
        return;
    }

    //If client is not connected, make sure that only LoginRequest can be executed
    if(!connected)
    {
        if(reqType.compare("LOGIN") == 0)
        {
            if(client.Setup() == 0)
                connected = true;
            else
            {
                qDebug()<<"Failed to connect to server, make sure the server is running.";
                return;
            }
        }
        else
        {
            qDebug()<<"Action not performed since client is not connected to the server, login first.";
            return;
        }
    }

    encoder e;
    short tildaInRequest = 0;
    std::string request = uname; // uname, 0

    request = e.encode(request, uType); // uname~uType, 1
    tildaInRequest++;

    request = e.encode(request, reqType); // uname~uType~reqType, 2
    tildaInRequest++;

    if(!additionalInfo.empty()) //Adds the additional info if it is not empty
    {
        request = e.encode(request, additionalInfo);
        tildaInRequest++;
    }

    request = e.encode(++tildaInRequest, request); //Finalize the message by adding the number of tildas in front
    client.SendText(request);

    if(reqType.compare("LOGOUT") == 0)
    {
        connected = false;

        return;
    }
    //========== Done Sending ============

    //============ Recieving =============
    decoder d;

    std::string response = client.RecieveText();

    d.decode('~', response, returnInfo);

//    //for(int i=0; i<2;i++) std::cout<< "randomness: "<<(*returnInfo)[i]<<std::endl;
//    int size = atoi((*returnInfo)[0].c_str())+1;
//    std::cout<< "randomness: "<<size<<std::endl;

//    std::string *s = new std::string[size];
//    for(int i=0;i<size; i++){
//        s[i] = std::string((*returnInfo)[i]);
//    }
//    *returnInfo = s;
//    for(int i=0; i<2;i++) std::cout<< "randomness1: "<<(*returnInfo)[i]<<std::endl;

    return;
}
