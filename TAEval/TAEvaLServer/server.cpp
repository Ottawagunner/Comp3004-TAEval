#include "server.h"
#include "QDebug"
#include "string.h"
#include <sstream>

Server::Server()
{
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = 0; // bind to all interface addresses
    servaddr.sin_port = htons(5000);
}

void Server::Setup()
{
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(server,(sockaddr*)&servaddr,sizeof(servaddr)) < 0)
    {
        ERROR="Failed to Bind";
        qDebug()<<"Failed to Bind";
    }
    Listen();
}

void Server::Listen()
{
    listen(server, 100);  // 50 (the backlog) isn't really used on modern systems
    clilen = sizeof(cliaddr);
    client = accept(server,(sockaddr*)&servaddr, &clilen);  // addr gets info about client
}


std::string Server::ReciveText()
{
   ssize_t n;
   char buffer[255];
   n = read(client,&buffer,255);
   if (n<0){
       ERROR="FAILED TO READ";
       qDebug()<<"FAILED TO READ";
   }
   std::string out =(buffer);
   qDebug()<<"Received:";
   qDebug()<<buffer;
   return out;
}

void Server::SendText(std::string message)
{
    char data[255];
    strcpy(data, message.c_str());
    send(client, data, (size_t) strlen(data) + 1, 0);
    //qDebug()<<"Sent:";
    //qDebug()<<data;
}
