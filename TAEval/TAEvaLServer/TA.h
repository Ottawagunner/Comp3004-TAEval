#ifndef TA_H
#define TA_H

#include "User.h"
class TA:User{
public:
    TA(std::string,std::string,std::string);
    void save();
    void write();
};

#endif // TA_H
