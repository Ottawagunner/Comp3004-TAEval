#include "clientcontrol.h"

int main(int argc, char *argv[])
{
    //return a.exec();
    ClientControl *u = new ClientControl(argc, argv);
    u->run();
}
