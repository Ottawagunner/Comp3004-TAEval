#include "clientcontrol.h"
#include <QDebug>

ClientControl::ClientControl(int argc, char **argv)
{
    ui = new UIController(this, argc, argv);
}
int ClientControl::run(){
    ui->run();
    return 0;
}
void ClientControl::giveRequest(std::string uname, char uType, std::string reqType, std::string additionalInfo){
    //SEND TO ENCODER
    //RECEIVE STRING FROM ENCODER
    //SEND THROUGH COMMS
    qDebug()<<reqType.c_str()<<" "<<uname.c_str()<<additionalInfo.c_str()<<" "<< uType;
}
