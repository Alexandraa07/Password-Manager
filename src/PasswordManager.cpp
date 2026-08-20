#include "PasswordManager.h"
#include "CryptoManager.h"

std::string PasswordManager::encrypt(const std::string &data)
{
    return CryptoManager::encrypt(data, masterPasswordHash);
}

std::string PasswordManager::decrypt(const std::string &data)
{
    return CryptoManager::decrypt(data, masterPasswordHash);
}

PasswordManager::PasswordManager()
{
    storage.loadFromFile(masterPasswordHash, entries);
    hasExistingMaster = !masterPasswordHash.empty();
}

void PasswordManager::setMasterPassword(const std::string &newPass)
{
    masterPasswordHash = CryptoManager::hashPassword(newPass);
    hasExistingMaster = true; 
    storage.saveToFile(masterPasswordHash, entries);
}

bool PasswordManager::login(const std::string &inputPass)
{
    return CryptoManager::hashPassword(inputPass) == masterPasswordHash;
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
