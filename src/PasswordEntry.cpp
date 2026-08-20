#include "PasswordEntry.h"

PasswordEntry::PasswordEntry() = default;

PasswordEntry::PasswordEntry(const std::string &website, const std::string &username, const std::string &password) : website(website), username(username), password(password) {}

void PasswordEntry::setWebsite(const std::string &website)
{
    this->website = website;
}

void PasswordEntry::setUsername(const std::string &username)
{
    this->username = username;
}

void PasswordEntry::setPassword(const std::string &password)
{
    this->password = password;
}

const std::string& PasswordEntry::getWebsite() const
{
    return website;
}

const std::string& PasswordEntry::getUsername() const
{
    return username;
}

const std::string& PasswordEntry::getPassword() const
{
    return password;
}