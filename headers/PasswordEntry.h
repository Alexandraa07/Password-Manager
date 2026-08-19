#pragma once
#include <string>

class PasswordEntry {
private:
    std::string website;
    std::string username;
    std::string password;

public:
    PasswordEntry();
    PasswordEntry(const std::string& website, const std::string& username, const std::string& password);

    void setWebsite(const std::string& website);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);

    const std::string& getWebsite() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
};