#include "PasswordManager.h"
#include <fstream>
#include <iostream>

std::string PasswordManager::simpleHash(const std::string &input)
{
    unsigned long hash = 0;
    for (char c : input)
        hash = (hash * 31 + c) % 1000000;
    return std::to_string(hash);
}

std::string PasswordManager::encrypt(const std::string &data)
{
    if (masterPasswordHash.empty())
        return data;

    std::string result = data;
    for (size_t i = 0; i < data.size(); ++i)
        result[i] = data[i] ^ masterPasswordHash[i % masterPasswordHash.size()];

    return result;
}

std::string PasswordManager::decrypt(const std::string &data)
{
    return encrypt(data); // XOR reversibil
}

PasswordManager::PasswordManager()
{
    loadFromFile();
}

void PasswordManager::setMasterPassword(const std::string &newPass)
{
    masterPasswordHash = simpleHash(newPass);
}

bool PasswordManager::login(const std::string &inputPass)
{
    return simpleHash(inputPass) == masterPasswordHash;
}

void PasswordManager::addEntry(const std::string &site, const std::string &user, const std::string &pass)
{
    if (site.empty() || pass.empty() || user.empty())
    {
        std::cout << "Site, user and password cannot be empty!\n";
        return;
    }

    if (entries.find(site) != entries.end())
    {
        std::cout << "Entry already exists!\n";
    }

    std::string encrypted = encrypt(pass);
    entries[site] = PasswordEntry(site, user, encrypted);

    saveToFile();

    std::cout << "Succesfully saved!\n";
}

bool PasswordManager::getEntry(const std::string &site, PasswordEntry &out)
{
    auto it = entries.find(site);
    if (it == entries.end())
        return false;

    out = it->second;
    out.setPassword(decrypt(out.getPassword()));
    return true;
}

void PasswordManager::deleteEntry(const std::string &site)
{
    if (entries.erase(site))
    {
        saveToFile();
        std::cout << "Succesfully deleted!\n";
    }
    else
        std::cout << "This site doesn't exist!\n";
}

void PasswordManager::saveToFile()
{
    std::ofstream f("passwords.txt");
    if (!f)
        return;

    f << masterPasswordHash << "\n";

    for (auto &pair : entries)
    {
        f << pair.second.getWebsite() << " "
          << pair.second.getUsername() << " "
          << pair.second.getPassword() << "\n";
    }
}

void PasswordManager::loadFromFile()
{
    std::ifstream f("passwords.txt");
    if (!f)
    {
        hasExistingMaster = false;
        return;
    }

    entries.clear();
    std::getline(f, masterPasswordHash);
    hasExistingMaster = !masterPasswordHash.empty();

    std::string site, user, pass;
    while (f >> site >> user >> pass)
    {
        entries[site] = PasswordEntry(site, user, pass);
    }
}

bool PasswordManager::isFirstRun() const
{
    return !hasExistingMaster;
}
