#pragma once
#include <string>

class CryptoManager
{
public:
    static bool init();
    static std::string hashPassword(const std::string &plainText);

    static std::string encrypt(const std::string &plainText, const std::string &keyHex);
    static std::string decrypt(const std::string &cypherText, const std::string &keyHex);
};