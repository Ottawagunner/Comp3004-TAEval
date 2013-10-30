#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QDebug>
#include "Database.h"

class Controller
{

public:
    Controller();
    ~Controller();
    void parse(std::string);
    void handleMessage(std::string);
    void executeMessage(std::string);

private:
    const static short messageLength = 4;
    std::string message[messageLength];
    Database database;
};

#endif // CONTROLLER_H
