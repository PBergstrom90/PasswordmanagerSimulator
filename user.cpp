#include <iostream>
#include <string>
#include "user.h"

User::User(std::string username, std::string password) : username(username), password(password){
}

std::string User::getUsername(){
    return username;
}

std::string User::getPassword(){
    return password;
}

void User::setUsername(std::string username){
this->username = username;
}

void User::setPassword(std::string password){
this->password = password;
}

void User::printUser(){
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
};