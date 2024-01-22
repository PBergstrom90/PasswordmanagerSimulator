#ifndef __USER_H
#define __USER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <openssl/md5.h>

class User {
    public:
        User(std::string username, std::string password, std::string salt);
        User();
        std::string getUsername();
        std::string getPassword();
        void setUsername(std::string username);
        void setPassword(std::string password);
        void printUser();
        User createUser(std::ifstream &userFile);
        friend std::istream& operator>>(std::istream& is, User& user);
        friend std::ostream& operator<<(std::ostream& os, const User& user);
    private:
        std::string username;
        std::string password;
        std::string salt;
};

std::string calculateMD5(std::string &input);

#endif // __USER_H