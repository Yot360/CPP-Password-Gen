#include <stdio.h>
#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string sha256(const std::string str) //converts string to sha256
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main(int argc, char const *argv[])
{
    
    int MINIMUM_PASSWORD_LENGTH = 12;

    int passlen = 0;
    std::string specialcharacters = "!@#$'%^\"&*()[]{}-_";

    while (passlen < MINIMUM_PASSWORD_LENGTH)
    {
        printf("Insert the password desired length.\n##Minimum 12 characters required##\n");
        std::cin>>passlen;
        if (std::cin.fail())
        {
            printf("You did not insert a number, try another time exiting...");
            return 0;
        }

        if (passlen < MINIMUM_PASSWORD_LENGTH)
        {
            printf("Password is too short!\n");
        }
        
    }
    
    std::string source = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" + specialcharacters;
    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(source.begin(), source.end(), generator);
    
    std::string password = source.substr(0, passlen); //generate password

    //check if password is in file
    std::ifstream file("passwords.txt");
    std::string str;
    while (std::getline(file, str))
    {
        if (password.find(str) != std::string::npos) {
            std::cout << "Password found in the password list: "<< str << '\n';
        }
    }

    std::cout<< "Password: " << password <<std::endl;
    std::cout<< "Password hash: " << sha256(password) <<std::endl;

    return 0;
}