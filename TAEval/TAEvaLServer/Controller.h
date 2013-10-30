#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QDebug>
#include "Database.h"

class Controller
{

public:
    Controller();
    void parse(std::string);
    void executeMessage(std::string);

private:
    std::string message[4];
    Database database;
};

#endif // CONTROLLER_H
