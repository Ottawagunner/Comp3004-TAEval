#ifndef TA_H
#define TA_H

#include "User.h"
class TA:User{
public:
    TA(Database* d);
    void search(std::string, std::string[]);
};

#endif // TA_H
