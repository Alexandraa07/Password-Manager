#include <iostream>
#include <limits>
#include "PasswordManager.h"
#include "CryptoManager.h"

int main()
{
    if (!CryptoManager::init())
    {
        std::cerr << "Eroare la initializarea CryptoManager!\n";
        return 1;
    }

    int option;
    PasswordManager manager;
    std::string masterPass;

    if (manager.isFirstRun())
    {
        std::cout << "Choose a master password!\n";
        std::getline(std::cin, masterPass);
        manager.setMasterPassword(masterPass);
    }
    else
    {
        std::cout << "Enter the master password!\n";
        std::getline(std::cin, masterPass);
        if (!manager.login(masterPass))
        {
            std::cout << "Incorrect password!\n";
            return 0;
        }
    }

    do
    {
        std::cout << "\n1-Add\n2-Search\n3-Delete\n4-Leave\n";
        std::cout << "Choose: ";
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
            if(manager.addEntry(site, user, pass))
            {
                std::cout << "Successfully saved\n";
            }
            else 
            {
                std::cout << "Could not be saved\n";
            }
            break;

        case 2:
            std::cout << "Site: ";
            std::getline(std::cin, site);
            {
                PasswordEntry e;
                if (manager.getEntry(site, e))
                {

                    std::cout << "User: " << e.getUsername() << "\n";
                    std::cout << "Pass: " << e.getPassword() << "\n";
                }
                else
                {
                    std::cout << "Couldn't be found.\n";
                }
            }
            break;

        case 3:
            std::cout << "Site: ";
            std::getline(std::cin, site);
            if(manager.deleteEntry(site))
            {
                std::cout << "Successfully deleted\n";
            }
            else 
            {
                std::cout << "Could not delete entry\n";
            }
            break;

        case 4:
            std::cout << "Saved data!\n";
            break;
        }

    } while (option != 4);

    return 0;
}