#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QDebug>

class Controller
{

public:
    Controller(std::string,std::string,std::string);
    void parse(std::string);

private:
    std::string message[4];
};

#endif // CONTROLLER_H
