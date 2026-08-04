#include <iostream>
#include <limits>
#include "PasswordManager.h"

int main()
{
    int option;
    PasswordManager manager;
    std::string masterPass;

    if (manager.isFirstRun())
    {
        std::cout << "Choose a master password!\n";
        std::getline(std::cin, masterPass);
        manager.setMasterPassword(masterPass);
        manager.saveToFile();
    }
    else
    {
        std::cout << "Enter the master password!\n";
        std::getline(std::cin, masterPass);
        if (!manager.login(masterPass))
        {
            std::cout << "Inccorect password!\n";
            return 0;
        }
    }

    do
    {
        std::cout << "\n1-ADAUGARE\n2-CAUTARE\n3-STERGERE\n4-IESIRE\n";
        std::cout << "Alege: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string site, user, pass;

        switch (option)
        {
        case 1:
            std::cout << "Site: ";
            std::getline(std::cin, site);
            std::cout << "User: ";
            std::getline(std::cin, user);
            std::cout << "Pass: ";
            std::getline(std::cin, pass);
            manager.addEntry(site, user, pass);
            break;

        case 2:
            std::cout << "Site: ";
            std::getline(std::cin, site);
            {
                PasswordEntry e = manager.getEntry(site);
                if (e.getWebsite() != "Inexistent")
                {
                    std::cout << "User: " << e.getUsername() << "\n";
                    std::cout << "Pass: " << e.getPassword() << "\n";
                }
                else
                {
                    std::cout << "Nu a fost gasit.\n";
                }
            }
            break;

        case 3:
            std::cout << "Site: ";
            std::getline(std::cin, site);
            manager.deleteEntry(site);
            break;

        case 4:
            manager.saveToFile();
            std::cout << "Date salvate!\n";
            break;
        }

    } while (option != 4);

    return 0;
}