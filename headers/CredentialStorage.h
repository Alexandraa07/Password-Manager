#pragma once

#include <map>
#include <string>
#include "PasswordEntry.h"

class CredentialStorage
{
public:
    bool saveToFile(const std::string& masterPasswordHash, const std::map<std::string, PasswordEntry>& entries);
    bool loadFromFile(std::string& masterPasswordHash, std::map<std::string, PasswordEntry>& entries);
};