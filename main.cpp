#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include "user.h"

void createAccount();
void initializeTextFile();
void adminMenu();

// DRIVER CODE
int main()
{
    
    initializeTextFile();
    adminMenu();
    
    return 0;
};

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

void createAccount(){
    User user = user.createUser();
};

void adminMenu(){
    bool isRunning = true;
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
            createAccount();
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