#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QDebug>

class Controller
{

public:
    Controller();
    void parse(std::string);
    void executeMessage(std::string);

private:
    std::string message[4];
};

#endif // CONTROLLER_H
