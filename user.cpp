#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include "user.h"

std::string calculateMD5(std::string &input) {
    MD5_CTX md5Context;
    MD5_Init(&md5Context);
    MD5_Update(&md5Context, input.c_str(), input.length());
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_Final(hash, &md5Context);
    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

User::User(std::string username, std::string password, std::string salt) : username(username), password(password), salt(salt){
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
 
 // For reading from file.
std::istream& operator>>(std::istream& is, User& user) {
    is >> user.username >> user.password;
    return is;
}
// For writing to file.
std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.username << ':' << user.password;
    return os;
}

void User::printUser(){
    std::cout << "Username: " << getUsername() << std::endl;
    std::cout << "Password: " << getPassword() << std::endl;
}

User User::createUser(){
    bool repeat = true;
    while(repeat){
    std::string username;
    std::string password;
    std::string salt;
    std::string nordicLetters = "åÅäÄöÖ";
    
    // Username-check
    std::cout << "\nEnter username: ";
    std::cin >> username;
    if(username.length() < 8){
        std::cout << "Username must be at least 8 characters long." << std::endl;
        continue;
    } 
    if(username.find('@') == std::string::npos){
        std::cout << "Username must contain @." << std::endl;
        continue;
    } else if(username.find('.') == std::string::npos){
        std::cout << "Username must contain a '.' " << std::endl;
        continue;
    } else if (username.find_first_of(nordicLetters) != std::string::npos) {
        std::cout << "Username cannot contain Nordic letters." << std::endl;
        continue;
    }
    
    // Password-check
    std::cout << "\nEnter password: ";
    std::cin >> password;


    std::string hashedPassword = calculateMD5(password);
    User user(username, hashedPassword, salt);
    std::ofstream file("users.txt", std::ios::app);
      if (file.is_open()) {
        file << user << '\n';
        file.close();
        } else {
        std::cout << "ERROR: Unable to open file" << std::endl;
        }
    std::cout << "\nUser created successfully!" << std::endl;
    repeat = false;
    user.printUser();
    return user;
    }
};