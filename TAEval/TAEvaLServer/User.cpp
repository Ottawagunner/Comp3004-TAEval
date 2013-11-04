#include "User.h"

User::User(Database *d)
{
    database = d;
}

std::string User::getName()
{
    return name;
}

std::string User::getUserName()
{
    return userName;
}

std::string User::getEmail()
{
    return email;
}

short User::login(std::string userName, std::string *response)
{
    //Database call to look for the userName and respond if it is found or not
    *response = "Login Successful";
    return 0;
}

short User::logout(std::string userName, std::string* response)
{
    //Database call to log out the user
    *response = "Logout Successful";
    return 0;
}
