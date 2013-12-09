#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QDebug>
#include "DatabaseInterface.h"
#include "mainwindow.h"
#include "decoder.h"
#include "encoder.h"
#include <cstdlib>
#include <string>

class Controller
{

public:
    Controller(int, std::string, std::string*);
    ~Controller();
    void parse(std::string*);
    void handleMessage(std::string*, std::string *);
    void executeMessage(std::string *);
    int runServer();
    Server host;

private:
    const static short messageLength = 4;
    std::string message[messageLength];
    DatabaseInterface dbi;
    bool listening;
};

#endif // CONTROLLER_H
