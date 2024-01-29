#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include "user.h"
#include "crack.h"

std::string calculateSHA256(const std::string &input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

std::string decryptSHA256(const std::string &input){
    
    std::stringstream ss;

    return ss.str();
};

std::string decryptMD5(const std::string &input){
    
    std::stringstream ss;

    return ss.str();    
};


void convertPasswordMD5(){
    std::string input;
    std::cout << "\n--- MD5 ---" << std::endl;
    std::cout << "Please enter a password: ";
    std::cin >> input;
    std::cout << "\nMD5 hash: " << calculateMD5(input) << std::endl;
};

void convertPasswordSHA256(){
    std::string input;
    std::cout << "\n--- SHA256 ---" << std::endl;
    std::cout << "Please enter a password: ";
    std::cin >> input;
    std::cout << "\nSHA256 hash: " << calculateSHA256(input) << std::endl;
};

void crackMD5(){
    std::string input;
    std::cout << "\n--- MD5 ---" << std::endl;
    std::cout << "Please enter a MD5 hash: ";
    std::cin >> input;
    std::cout << "\nMD5 in plaintext: " << decryptMD5(input) << std::endl;
};

void crackSHA256(){
    std::string input;
    std::cout << "\n--- SHA256 ---" << std::endl;
    std::cout << "Please enter a SHA256 hash: ";
    std::cin >> input;
    std::cout << "\nSHA256 in plaintext: " << decryptSHA256(input) << std::endl;
};

void crackPassword(){
            std::cout << "1. Convert to MD5" << std::endl;
            std::cout << "2. Convert to SHA256" << std::endl;
            std::cout << "3. Crack MD5 password" << std::endl;
            std::cout << "4. Crack SHA256 password" << std::endl;
            std::cout << "Enter your choice: ";
            int choice = 0;
            std::cin >> choice;
            switch(choice) {
                case 1:
                    convertPasswordMD5();
                    break;
                case 2:
                    convertPasswordSHA256();
                    break;
                case 3:
                    crackMD5();
                    break;
                case 4:
                    crackSHA256();
                    break;
                default:
                    std::cout << "\nInvalid choice. Please try again." << std::endl;
                    break;
            }
};