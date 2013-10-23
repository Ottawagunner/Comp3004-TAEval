#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User{

public:
    User(string,string,string);
    string getUserName();
    string getName();
    string getEmail();
    virtual void save() = 0;
    virtual void write() = 0;


protected:
    string userName;
    string name;
    string email;
};


#endif // USER_H
