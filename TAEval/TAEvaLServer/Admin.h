#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
class Admin:User{
public:
    Admin(std::string,std::string,std::string,Database* d);
    void search(std::string, std::string[]);
};

#endif // ADMIN_H
