#ifndef SERVER_H
#define SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <netdb.h>

class Server
{
public:
    Server();
    std::string ERROR;
    int sockfd;
    struct sockaddr_in server;
    struct addrinfo *serverinfo;

    ssize_t bytesreceived;

    void SendText(std::string);
    std::string ReciveText();
    void Setup();
};

#endif // SERVER_H
