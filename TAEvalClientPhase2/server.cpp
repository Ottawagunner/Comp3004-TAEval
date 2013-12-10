#include "server.h"
#include "string.h"
#include <fstream>
#include <QDebug>

Server::Server()
{
}

short Server::Setup(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::ifstream myfile("config.txt");
    std::string buffer;
    if(myfile)
        std::getline(myfile, buffer);
    else buffer = "localhost";
    qDebug()<<buffer.c_str();
    getaddrinfo(buffer.c_str(), NULL, NULL, &serverinfo);

    /*Copy size of sockaddr_in b/c res->ai_addr to big for this example*/
    memcpy (&server, serverinfo->ai_addr, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    if(myfile)
        std::getline(myfile, buffer);
    else buffer = "5000";
    qDebug()<<buffer.c_str();

    server.sin_port = htons(atoi(buffer.c_str()));
    freeaddrinfo(serverinfo);

    if (connect(sockfd, (const struct sockaddr *) &server,sizeof(struct sockaddr_in))<0){
        qDebug()<<"ERROR CONNECTING";
        return -1;
    }
    return 0;
}

void Server::SendText(std::string message)
{
    char data[255];
    strcpy(data, message.c_str());
    send(sockfd, data, (size_t) strlen(data) + 1, 0);
    //qDebug()<<"Sent:";
    //qDebug()<<data;
}

std::string Server::RecieveText()
{
   ssize_t n;
   char buffer[255];
   n = read(sockfd,&buffer,255);
   if (n<0){
       ERROR="FAILED TO READ";
       qDebug()<<"FAILED TO READ";
   }
   std::string out =(buffer);
   //qDebug()<<"Received:";
   //qDebug()<<buffer;
   return out;
}
