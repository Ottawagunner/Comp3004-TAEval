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
    server.sin_port = htons(2000);
    freeaddrinfo(serverinfo);

    if (connect(sockfd, (const struct sockaddr *) &server,sizeof(struct sockaddr_in))<0){
        qDebug()<<"ERROR CONNECTING";
    }else{
        qDebug()<<"CONNECTED";
    }

}
void Server::Send(){
    send(sockfd, "TEST String", (size_t) strlen("TEST String") + 1, 0);
}
