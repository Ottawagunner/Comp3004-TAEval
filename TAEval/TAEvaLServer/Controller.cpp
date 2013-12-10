#include <QDebug>
#include "Controller.h"

using namespace std;

Controller::Controller(int size, std::string path, std::string* fileList) : dbi(size, path, fileList)
{
    for(int i=0; i<messageLength;i++)
        message[i] = "";
}

Controller::~Controller()
{
   // delete &database;
}

int Controller::runServer(){
    //QApplication a(argc, argv);
    //MainWindow w;
    host.Setup();
    while(true)
    {
        listening = true;
        do{
            std::string buffer = (host.ReciveText());
            if(buffer.empty()) break;
            executeMessage(&buffer);
            host.SendText(buffer);
        }while(listening);
        listen(host.server, 100);  // 50 (the backlog) isn't really used on modern systems
        host.clilen = sizeof(host.cliaddr);
        host.client = accept(host.server,(sockaddr*)&(host.servaddr), &(host.clilen));  // addr gets info about client
    }
    //w.show();
    //return a.exec();
}

void Controller::executeMessage(std::string *command)
{
    decoder decode = *new decoder();
    std::string* parsedCommand;

    decode.decode('~', *command, &parsedCommand);
    //for(int i=0; i<5;i++) std::cout<<parsedCommand[i]<<std::endl;
    handleMessage(parsedCommand, command);
}

void Controller::handleMessage(std::string *command, std::string* response) // finds the userType which is one of A, I or T, created an object of the proper class and passes on the request
{
    //for(int i=0; i<5;i++) std::cout<<command[i]<<std::endl;

    // send the message to the database
    std::string* result;


    dbi.handleRequest(&command,&result);


    // Encoding function once db works
    // Loops through something like this
    //std::string result[8]= {"2", "2", "3", "Title of Task 1", "Description of Task1 like he's good", "Alpha", "Beta", "Gamma"};
    //                        [0]  [1]  [2]      [3]                    [4]                              [5]      [6]     [7]
    //std::cout<<result[0]<<std::endl;
    if(result == NULL){
        result = new std::string[3];
        result[0]="1";
        result[1]="1";
        result[2]="SUCCESS";
    }
    std::cout << "result[0]: " << result[0] << std::endl;
    std::cout << "result[1]: " << result[1] << std::endl;
    std::cout << "result[2]: " << result[2] << std::endl;

    encoder e;
    std::string output = "";
    short tildaInRequest = 0;
    short numberOfData = 0;
    for(int i = 1; i < atoi(result[0].c_str()) +1 ; i++) // Find out how many data blocks was given by the db
        numberOfData+=atoi(result[i].c_str());
    std::cout<<"do I crash after this?d"<<std::endl;
    for(int j = 0; j < numberOfData; j++) // Loops through all of the data and encodes them into a single string
    {
        output = e.encode(output, result[atoi(result[0].c_str())+1+j]);
        std::cout<<j<<std::endl;
        std::cout<<output<<std::endl;
        tildaInRequest++;
    }
    std::cout<<"do I crash after this?s"<<std::endl;
    output = output.substr(1, -1); // cuts the first tilda off
    output = e.encode(tildaInRequest, output); // adds the number of tildas through the encoder (adds the tilda we cut off)
    *response = output;
        std::cout<<"do I crash after thissadas?"<<std::endl;
}

