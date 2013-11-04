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

std::string User::encode(short listLength, std::string* list)
{
    std::string encodedList = "";
    for(int i=0; i<listLength; i++)
    {
        encodedList+=list[i];
        if(i+1 < listLength)
            encodedList+="~";
    }
}

std::string User::encode(std::string original, std::string toAdd)
{
    return original+toAdd;
}
