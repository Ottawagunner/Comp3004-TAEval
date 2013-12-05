#ifndef USER_H
#define USER_H
#include <string>
#include "Database.h"
#include <QDebug>
#include <stdio.h>
#include "decoder.h"
#include "encoder.h"
class User{

public:
    User(Database*);
    std::string getUserName();
    std::string getName();
    std::string getEmail();
    virtual void search(std::string,std::string[]) = 0;
    short login(std::string, std::string*);
    short logout(std::string, std::string*);


protected:
    std::string userName;
    std::string name;
    std::string email;
    Database* database;
};

#endif // USER_H
