#include "User.h"

User::User(string u, string n, string e){
    userName = u;
    name = n;
    email = e;
}
string User::getName(){
    return name;
}
string User::getUserName(){
    return userName;
}
string User::getEmail(){
    return email;
}
short User::login(){
return 0;
}

short User::logout(){
return 0;
}
