#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{

public:
    Controller();
    ~Controller();
    std::string* parse(std::string, int);
    void handleMessage(std::string);

private:
};

#endif // CONTROLLER_H


