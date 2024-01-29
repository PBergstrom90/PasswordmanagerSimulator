#ifndef __CRACK_H
#define __CRACK_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
#include <openssl/sha.h>

std::string calculateSHA256(const std::string &input);
void crackMenu();
void convertPasswordMD5();
void convertPasswordSHA256();
void crackMD5();
void crackSHA256();
std::string decryptMD5(const std::string &input);
std::string decryptSHA256(const std::string &input);

#endif // __CRACK_H 