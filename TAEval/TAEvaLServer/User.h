#ifndef USER_H
#define USER_H
#include <string>
#include "Database.h"
class User{

public:
    User(std::string,std::string,std::string, Database*);
    std::string getUserName();
    std::string getName();
    std::string getEmail();
    virtual void search() = 0;
    short login();
    short logout();


protected:
    std::string userName;
    std::string name;
    std::string email;
    Database* database;
};


#endif // USER_H
