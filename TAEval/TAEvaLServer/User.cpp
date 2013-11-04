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

std::string User::encode(short messageLength, std::string lockStatus, std::string message)
{
    std::stringstream mL;
    mL << messageLength;
    return ""+mL.str()+"~"+lockStatus+"~"+message;
}
