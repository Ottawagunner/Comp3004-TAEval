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
    std::string testArr[4] = {"4","DID","NOT","WORK"};
    ////////////////////LOGIN TEST/////////////////////////////////////////

    if((reqType.compare("LOGIN")==0)){
        testArr[0]="4";
        testArr[1]="Instructor";
        testArr[2]="Log";
        testArr[3]="in";
    }
    if(reqType.compare("VIEWONETASK")==0){
        testArr[0]="3";
        testArr[1]="VIEW";
        testArr[2]="ONE TASK";
        testArr[3]="";
    }
    if(reqType.compare("VIEWALLTASKS")==0){
        testArr[0]="4";
        testArr[1]="VIEW";
        testArr[2]="ALL";
        testArr[3]="TASKS";
    }
    if(reqType.compare("VIEWONEEVAL")==0){
        testArr[0]="3";
        testArr[1]="VIEW";
        testArr[2]="ONE EVAL";
        testArr[3]="";
    }
    if(reqType.compare("VIEWALLEVALS")==0){
        testArr[0]="4";
        testArr[1]="VIEW";
        testArr[2]="ALL";
        testArr[3]="EVALUATIONS";
    }
    if(reqType.compare("VIEWALLTASKS")==0){
        testArr[0]="4";
        testArr[1]="VIEW";
        testArr[2]="ALL";
        testArr[3]="TASKS";
    }
    if(reqType.compare("VIEWALLTAS")==0){
        testArr[0]="4";
        testArr[1]="VIEW";
        testArr[2]="ALL";
        testArr[3]="TAS";
    }
    /////////////////////////////////////////////////////////////////////////

    ////////////////////
    /*if((reqType.compare("VIEWALLTASKS")==0)||(reqType.compare("VIEWALLEVALS"))){
        std::string viewListTest[5] = {"5","KILL THE BATMAN", "WHY SO SERIOUS", "WANNA KNOW HOW I GOT THESE SCARS?", "ARROW"};
        std::stringstream convert(viewListTest[0]);
        int size;
        convert>>size;
        std::string *s = new std::string[size];
        for(int i=0;i<size; i++){
            s[i] = viewListTest[i];
        }
        *returnInfo = s;
    }
    else{
        std::string *s = new std::string[2];
        s[0]= "2";
        s[1]= "FAILED TO COMPARE";
        *returnInfo = s;

    }*/
    std::stringstream convert(testArr[0]);
    int size;
    convert>>size;
    std::string *s = new std::string[size];
    for(int i=0;i<size; i++){
        s[i] = testArr[i];
    }
    *returnInfo = s;
    //Checks all 3 necessary arguments to make sure all of them are well-defined
    /*if(uname.empty())
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
        if(reqType.compare("LOGINREQUEST") == 0)
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

    if(reqType.compare("LOGOUTREQUEST") == 0)
    {
        connected = false;
        *returnInfo = std::string("Logged out");
        return;
    }
    //========== Done Sending ============

    //============ Recieving =============
    decoder d;

    std::string response = client.RecieveText();

    d.decode('~', response, &returnInfo);*/

    return;
}
