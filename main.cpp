#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include "user.h"

void hashCommonPasswords();
std::string calculateMD5(const std::string &input);
void initializeTextFile();
void adminMenu();

// DRIVER CODE
int main()
{
    
    initializeTextFile();
    adminMenu();
    
    return 0;
};

std::string calculateMD5(const std::string &input) {
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

void initializeTextFile(){
    std::ifstream file("users.txt");
    std::string line;
    std::vector<User> users;
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string username;
        std::string password;
        iss >> username >> password;
        User user(username, password);
        users.push_back(user);
    }
    file.close();
};

void adminMenu(){
    bool isRunning = true;
    std::string username;
    std::string password;
    while(isRunning){
    std::cout << "\n--- ADMIN MENU ---" << std::endl;
    std::cout << "1. Create Account" << std::endl;
    std::cout << "2. Test login" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    int choice = 0;
    std::cin >> choice;
    switch(choice) {
        case 1:
            std::cout << "\n--- CREATE ACCOUNT ---" << std::endl;
            std::cout << "Enter username (email): ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;
            std::cout << "Account created successfully!" << std::endl;
            break;
        case 2:
            std::cout << "\n--- TEST LOGIN ---" << std::endl;
            break;
        case 3:
            std::cout << "\nProgram closing... " << std::endl;
            isRunning = false;
            break;
        default:
            std::cout << "\nInvalid choice. Please try again." << std::endl;
            break;
        }
    }
};