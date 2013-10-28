#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
public:
    Server();

    int client,server;
    socklen_t clilen;
    std::string ERROR;
    struct sockaddr_in servaddr, cliaddr;
    //bzero(&addr, sizeof(addr));


    void Setup();
    void SendText(std::string);
    std::string ReciveText();
};

#endif // SERVER_H
