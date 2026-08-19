#pragma once
#include <map>
#include <string>
#include "PasswordEntry.h"
#include "CredentialStorage.h"

class PasswordManager
{
private:
    CredentialStorage storage;
    bool hasExistingMaster = false;
    std::map<std::string, PasswordEntry> entries;
    std::string masterPasswordHash;

    std::string encrypt(const std::string &data);
    std::string decrypt(const std::string &data);
    std::string simpleHash(const std::string &input);

public:
    PasswordManager();

    void setMasterPassword(const std::string &newPass);
    bool login(const std::string &inputPass);

    bool addEntry(const std::string &site, const std::string &user, const std::string &pass);
    bool getEntry(const std::string &site, PasswordEntry &out);
    bool deleteEntry(const std::string &site);

    bool isFirstRun() const;
};