#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
class Admin:User{
public:
    Admin(string,string,string);
    void save();
    void write();
};

#endif // ADMIN_H
