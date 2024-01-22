#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <openssl/md5.h>
#include "user.h"

void createAccount();
void login();
void adminMenu();

// DRIVER CODE
int main()
{
    
    adminMenu();
    
    return 0;
};

void createAccount(){
    std::ifstream userFile("users.txt");
    if (!userFile.is_open()) {
        std::cout << "File not found. Creating a new users.txt file." << std::endl;
        std::ofstream newFile("users.txt");
        newFile.close();
        userFile.open("users.txt");
    }

    if (userFile.is_open()) {
        std::cout << "File opened successfully." << std::endl;
        User user = user.createUser(userFile);
        userFile.close();  // Close the file after using it
    } else {
        std::cout << "Error opening file." << std::endl;
    }
};

void login() {
    std::string username;
    std::string password;
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
            std::cout << "\nEnter password: ";
            std::cin >> password;
            std::string hashedPassword = calculateMD5(password);
            if (user.getPassword() == hashedPassword) {
                std::cout << "\nLogin successful!" << std::endl;
                std::cout << "Welcome: " << user.getUsername() << std::endl;
            } else {
                std::cout << "\nIncorrect password. Please try again." << std::endl;
            }
        } else {
            std::cout << "\nUsername not found. Please check your username." << std::endl;
        }
    } else {
        std::cout << "Error opening file." << std::endl;
    }
}

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
            login();
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