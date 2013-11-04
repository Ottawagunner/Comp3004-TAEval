#ifndef USER_H
#define USER_H
#include <string>
#include "Database.h"
class User{

public:
    User(Database*);
    std::string getUserName();
    std::string getName();
    std::string getEmail();
    virtual void search(std::string,std::string[]) = 0;
    short login(std::string, std::string*);
    short logout(std::string, std::string*);
    std::string encode(short, std::string, std::string); //Final encoding before message is sent lengthOfMessage~lockStatus~Message
    std::string encode(short listLength, std::string* list); //Turns a list of n+1 string into list[0]~..~list[n]
    std::string encode(std::string, std::string); //Takes a string A and a string B and returns a string A~B

protected:
    std::string userName;
    std::string name;
    std::string email;
    Database* database;
};

#endif // USER_H
