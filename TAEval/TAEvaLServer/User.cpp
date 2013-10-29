#include "User.h"

User::User(std::string u, std::string n, std::string e, Database* d){
    userName = u;
    name = n;
    email = e;
    database = d;
}
std::string User::getName(){
    return name;
}
std::string User::getUserName(){
    return userName;
}
std::string User::getEmail(){
    return email;
}
short User::login(){
return 0;
}

short User::logout(){
return 0;
}
