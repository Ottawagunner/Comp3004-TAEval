#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QDebug>
#include "Database.h"
#include "mainwindow.h"

class Controller
{

public:
    Controller(int, std::string, std::string*);
    ~Controller();
    void parse(std::string*);
    void handleMessage(std::string *);
    void executeMessage(std::string *);
    int runServer(bool);
    Server host;

private:
    const static short messageLength = 4;
    std::string message[messageLength];
    Database database;
    bool listening;
};

#endif // CONTROLLER_H
