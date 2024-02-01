#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <openssl/md5.h>
#include "user.h"


std::string generateSalt() {
    int saltLength = 10; 
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, characters.size() - 1);
    std::string salt;
    for (int i = 0; i < saltLength; i++) {
        salt += characters[distribution(gen)];
    }
    return salt;
};

std::string calculateMD5(std::string &input) {
    MD5_CTX md5Context;
    MD5_Init(&md5Context);
    MD5_Update(&md5Context, input.c_str(), input.length());
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_Final(hash, &md5Context);
    std::stringstream hexHashStream;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        hexHashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return hexHashStream.str();
};

User::User(std::string username, std::string password, std::string salt) : username(username), password(password), salt(salt){
};
User::User() : username(""), password(""), salt("") {
};

std::string User::getUsername(){
    return username;
};

std::string User::getPassword(){
    return password;
};

std::string User::getSalt(){
    return salt;
};

void User::setUsername(std::string username){
this->username = username;
};

void User::setPassword(std::string password){
this->password = password;
};
 
// For reading from file.
std::istream& operator>>(std::istream& is, User& user) {
    std::string line;
    if (std::getline(is, line)) {
        // Find the position of the ':' character
        size_t firstColonPos = line.find(':');
        size_t secondColonPos = line.find(':', firstColonPos + 1);
        if (firstColonPos != std::string::npos && secondColonPos != std::string::npos) {
            // Extract username and password
            user.username = line.substr(0, firstColonPos);
            user.password = line.substr(firstColonPos + 1, secondColonPos - firstColonPos - 1);
            user.salt = line.substr(secondColonPos + 1);
        } else {
            // Handle the case where ':' is not found (format error)
            is.setstate(std::ios::failbit);
        }
    }
    return is;
};

// For writing to file.
std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.username << ':' << user.password << ':' << user.salt;
    return os;
};

// Password-check function.
    bool isUppercase(char c) {
        return std::isupper(c) != 0;
    };
    bool isLowercase(char c) {
        return std::islower(c) != 0;
    };
    bool isDigit(char c) {
        return std::isdigit(c) != 0;
    };
    bool isSpecialChar(char c) {
        std::string specialChars = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/";
        return specialChars.find(c) != std::string::npos;
    };
    bool isStrongPassword(const std::string& password) {
        bool hasLength = password.length() >= 8;
        bool hasUppercase = std::any_of(password.begin(), password.end(), isUppercase);
        bool hasLowercase = std::any_of(password.begin(), password.end(), isLowercase);
        bool hasNumber = std::any_of(password.begin(), password.end(), isDigit);
        bool hasSpecialChar = std::any_of(password.begin(), password.end(), isSpecialChar);
        return hasLength && hasUppercase && hasLowercase && hasNumber && hasSpecialChar;
    };

User User::createUser(std::ifstream &userFile){
    bool repeat = true;
    while(repeat){
    std::string username = " ";
    std::string password = " ";
    std::string salt = generateSalt();
    
    // Username-check.
    std::cout << "\nEnter username: ";
    std::cin >> username;
    std::ifstream userFile("users.txt");
    if (userFile.is_open()) {
    User user;
    bool usernameExists = false;
    while (userFile >> user) {
        if (user.getUsername() == username) {
            usernameExists = true;
            break;
        }
    }
    userFile.close();
    if (usernameExists) {
        std::cout << "Username already exists." << std::endl;
        continue;
        }
    } if(username.length() < 8){
        std::cout << "Username must be at least 8 characters long." << std::endl;
        continue;
    } if(username.find('@') == std::string::npos){
        std::cout << "Username must contain @." << std::endl;
        continue;
    } if(username.find('.') == std::string::npos){
        std::cout << "Username must contain a '.' " << std::endl;
        continue;
    } if(username.find(' ') != std::string::npos){
        std::cout << "Username must not contain spaces." << std::endl;
        continue;
    }

    // Password-check.
    std::cout << "\nEnter password: ";
    std::cin >> password;
    if (!isStrongPassword(password)) {
        std::cout << "The password is too weak. Each password requires: \n1. at least 8 characters.\n2. at least one uppercase-letter\n3. at least one lowercase-letter\n4. at least one digit.\n5. at least one specialcharacter." << std::endl;
        continue;
    }

    // Adding salt to password.
    std::string combinedString = password + salt;
    std::string hashedPassword = calculateMD5(combinedString);
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
    return user;
    }
};