#include "server.h"
#include "string.h"
#include <QDebug>
Server::Server()
{
}

void Server::Setup(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    getaddrinfo("localhost", NULL, NULL, &serverinfo);

    /*Copy size of sockaddr_in b/c res->ai_addr to big for this example*/
    memcpy (&server, serverinfo->ai_addr, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    freeaddrinfo(serverinfo);

    if (connect(sockfd, (const struct sockaddr *) &server,sizeof(struct sockaddr_in))<0){
        qDebug()<<"ERROR CONNECTING";
    }else{
        qDebug()<<"CONNECTED";
    }

}
void Server::SendText(std::string X)
{
    char data[255];
    strcpy(data,X.c_str());
    send(sockfd, data, (size_t) strlen(data) + 1, 0);
    qDebug()<<"Sent:";
    qDebug()<<data;
}

std::string Server::ReciveText()
{
   ssize_t n;
   char buffer[255];
   n = read(sockfd,&buffer,255);
   if (n<0){
       ERROR="FAILED TO READ";
       qDebug()<<"FAILED TO READ";
   }
   std::string out =(buffer);
   qDebug()<<"Received:";
   qDebug()<<buffer;
   return out;
}
