#include "PasswordManager.h"

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
    storage.loadFromFile(masterPasswordHash, entries);

    hasExistingMaster = !masterPasswordHash.empty();
}

void PasswordManager::setMasterPassword(const std::string &newPass)
{
    masterPasswordHash = simpleHash(newPass);
}

bool PasswordManager::login(const std::string &inputPass)
{
    return simpleHash(inputPass) == masterPasswordHash;
}

bool PasswordManager::addEntry(const std::string &site, const std::string &user, const std::string &pass)
{
    if (site.empty() || pass.empty() || user.empty())
    {
        return false;
    }

    if (entries.find(site) != entries.end())
    {
        return false;
    }

    std::string encrypted = encrypt(pass);
    entries[site] = PasswordEntry(site, user, encrypted);

    storage.saveToFile(masterPasswordHash, entries);

    return true;
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

bool PasswordManager::deleteEntry(const std::string &site)
{
    if (entries.erase(site) == 0)
    {
        return false;
    }
    storage.saveToFile(masterPasswordHash, entries);
    return true;
}

bool PasswordManager::isFirstRun() const
{
    return !hasExistingMaster;
}
