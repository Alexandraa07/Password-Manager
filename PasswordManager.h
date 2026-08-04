#pragma once
#include <map>
#include <string>
#include "PasswordEntry.h"

class PasswordManager {
private:
    bool hasExistingMaster = false;
    std::map<std::string, PasswordEntry> entries;
    std::string masterPasswordHash;

    std::string encrypt(const std::string& data);
    std::string decrypt(const std::string& data);
    std::string simpleHash(const std::string& input);

public:
    PasswordManager();

    void setMasterPassword(const std::string& newPass);
    bool login(const std::string& inputPass);

    void addEntry(const std::string& site, const std::string& user, const std::string& pass);
    PasswordEntry getEntry(const std::string& site);
    void deleteEntry(const std::string& site);

    void saveToFile();
    void loadFromFile();

    bool isFirstRun() const;
};