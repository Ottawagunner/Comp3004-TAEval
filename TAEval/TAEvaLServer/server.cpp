#include "server.h"
#include "QDebug"
Server::Server()
{
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = 0; // bind to all interface addresses
    servaddr.sin_port = htons(2000);
}
void Server::Setup()
{
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(server,(sockaddr*)&servaddr,sizeof(servaddr)) < 0){
        ERROR="Failed to Bind";

    }
    listen(server, 100);  // 50 (the backlog) isn't really used on modern systems
    clilen = sizeof(cliaddr);
    client = accept(server,(sockaddr*)&servaddr, &clilen);  // addr gets info about client


}
void Server::SendText(std::string* )
{

}
std::string Server::ReciveText()
{
   ssize_t n;
   std::string buffer;
   n = read(client,&buffer,255);
   if (n>0){
       ERROR="FAILED TO READ";
   }

   return buffer;
}
/*
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);
     if (newsockfd < 0)
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0;
*/
