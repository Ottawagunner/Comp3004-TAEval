#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include "User.h"
#include "Database.h"
#include <cstdlib>
#include <sstream>
#include <QDebug>
class Instructor:User{
public:
    Instructor(Database *database);
    void manageReq(std::string, std::string, std::string*);
    void search(std::string, std::string[]);
private:
    Database* d;
    std::string reqType[10];
};


#endif // INSTRUCTOR_H
