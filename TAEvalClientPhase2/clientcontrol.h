#ifndef CLIENTCONTROL_H
#define CLIENTCONTROL_H
#include "uicontroller.h"
#include "clientcontrol.h"
class UIController;
class ClientControl
{
public:
    ClientControl(int argc, char** argv);
    int run();
    void giveRequest(std::string, std::string, std::string, std::string, std::string* returnInfo);

private:
    UIController *ui;
};

#endif // CLIENTCONTROL_H
