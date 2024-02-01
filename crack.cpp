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
    std::stringstream hexHashStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hexHashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return hexHashStream.str();
};

std::string decryptSHA256(const std::string &input){
    std::ifstream inputFile("commonpasswordsSHA256.txt");
    if (!inputFile.is_open()) {
        std::cerr << "ERROR: Could not open input file." << std::endl;
        return "";
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string hashedPassword, password;
        iss >> hashedPassword >> password;
        if (input == hashedPassword) {
            inputFile.close();
            return password;
        }
    }
    inputFile.close();
    return "";
};

std::string decryptMD5(const std::string &input){
    std::ifstream inputFile("commonpasswordsMD5.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return "";
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string hashedPassword, password;
        iss >> hashedPassword >> password;
        if (input == hashedPassword) {
            inputFile.close();
            return password;
        }
    }
    inputFile.close();
    return "";
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
    std::string inputMD5;
    std::cout << "\n--- MD5 ---" << std::endl;
    std::cout << "Please enter a MD5 hash: ";
    std::cin >> inputMD5;
    std::string decryptedMD5 = decryptMD5(inputMD5);

    if(!decryptedMD5.empty()){
    std::cout << "\nMD5 in plaintext: " << decryptedMD5 << std::endl;
    } else {
        std::cout << "\nERROR: Could not generate plaintext." << std::endl;
    }
};

void crackSHA256(){
    std::string inputSHA256;
    std::cout << "\n--- SHA256 ---" << std::endl;
    std::cout << "Please enter a SHA256 hash: ";
    std::cin >> inputSHA256;
    std::string decryptedSHA256 = decryptSHA256(inputSHA256);
    
    if (!decryptedSHA256.empty()){
    std::cout << "\nSHA256 in plaintext: " << decryptedSHA256 << std::endl;
    } else {
        std::cout << "\nERROR: Could not generate plaintext." << std::endl;
    }
};

void crackMenu(){
    std::cout << "1. Convert to MD5" << std::endl;
    std::cout << "2. Convert to SHA256" << std::endl;
    std::cout << "3. Crack MD5 hash" << std::endl;
    std::cout << "4. Crack SHA256 hash" << std::endl;
    std::cout << "5. Return" << std::endl;
    std::cout << "Enter your choice: ";
    int choice2 = 0;
    std::cin >> choice2;
    switch(choice2) {
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
        case 5:
            std::cout << "\nReturning..." << std::endl;
            break;
        default:
            std::cout << "\nERROR: Invalid choice. Please try again." << std::endl;
            break;
    }
};