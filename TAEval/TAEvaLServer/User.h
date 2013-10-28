#ifndef USER_H
#define USER_H
#include <string>
class User{

public:
    User(std::string,std::string,std::string);
    std::string getUserName();
    std::string getName();
    std::string getEmail();
    virtual void save() = 0;
    virtual void write() = 0;
    short login();
    short logout();


protected:
    std::string userName;
    std::string name;
    std::string email;
};


#endif // USER_H
