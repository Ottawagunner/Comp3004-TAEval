#include "User.h"

User::User(std::string u, std::string n, std::string e){
    userName = u;
    name = n;
    email = e;
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
