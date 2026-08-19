#include "CredentialStorage.h"
#include <fstream>

bool CredentialStorage::saveToFile(const std::string &masterPasswordHash, const std::map<std::string, PasswordEntry> &entries)
{
    std::ofstream file("password.txt");

    if (!file)
    {
        return false;
    }

    file << masterPasswordHash << '\n';

    for (const auto &pair : entries)
    {
        file << pair.second.getWebsite() << ' ' << pair.second.getUsername() << ' ' << pair.second.getPassword() << '\n';
    }

    return true;
}

bool loadFromFile(std::string &masterPasswordHash, std::map<std::string, PasswordEntry> &entries)
{

    std::ifstream file("password.txt");

    if (!file)
    {
        return;
    }

    std::getline(file, masterPasswordHash);

    std::string site;
    std::string user;
    std::string pass;

    while (file >> site >> user >> pass)
    {
        entries[site] = PasswordEntry(site, user, pass);
    }
}
