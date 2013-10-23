#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include "User.h"
class Instructor:User{
public:
    Instructor(string u,string n,string e);
    void save();
    void write();
};


#endif // INSTRUCTOR_H
