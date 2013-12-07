#ifndef CLIENTCONTROL_H
#define CLIENTCONTROL_H
#include "uicontroller.h"
#include "clientcontrol.h"
#include "decoder.h"
#include "encoder.h"
#include "server.h"

class UIController;
class ClientControl
{
public:
    ClientControl(int argc, char** argv);
    int run();
    void giveRequest(std::string, std::string, std::string, std::string, std::string* returnInfo);

private:
    UIController *ui;
    Server client;
    bool connected;
};

#endif // CLIENTCONTROL_H
