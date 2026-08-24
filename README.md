# Secure Password Manager (C++)

A local command-line application built in modern **C++** for securely storing and managing credentials. The project focuses on clean Object-Oriented Programming (OOP), dynamic data structures, and safe local persistence powered by the **libsodium** library.

---

## Key Features & Security

- **Authenticated Encryption:** Passwords are encrypted before being written to disk using `crypto_secretbox`.
- **Master Password Hashing:** User authentication is handled via `crypto_generichash` (BLAKE2b). Plain-text master passwords are never stored.
- **Persistent Storage:** Encrypted entries are safely saved and loaded from disk (`data/passwords.txt`).
- **In-Memory Lookup:** Fast record search, insertion, and deletion using `std::map`.

---

## Technologies Used

- **Language:** C++20
- **Cryptography:** libsodium
- **Build System:** CMake (v3.15+)
- **Standard Library (STL):** `std::map`
- **Concepts:** Object-Oriented Programming, Data Structures

---

## Project Architecture

- **`CryptoManager`** – Encapsulates encryption, decryption, and hashing logic via libsodium.
- **`CredentialStorage`** – Handles file I/O operations (saving/loading data from disk).
- **`PasswordEntry`** – Data model representing a credential set (website, username, password).
- **`PasswordManager`** – Manages application workflow, authentication state, and entry lookup.
- **`main.cpp`** – Console interface and user menu navigation.

---

## How to Build and Run

### Prerequisites
- A C++20 compliant compiler (`g++`)
- **CMake** (v3.15 or newer)
- **libsodium** library installed

### Build Steps

```bash
1. Create data folder for storage
mkdir -p data

2. Build using CMake
mkdir build && cd build
cmake ..
cmake --build .

3. Run the executable
./password_manager
```

```bash
## How to Use it

1. First Launch: Set up your Master Password.

2. Subsequent Runs: Log in using your Master Password to unlock the vault.

3. Interactive Menu:
   1 - Add: Store a new website, username, and password.
   2 - Search: Look up stored credentials by website name.
   3 - Delete: Remove a stored entry.
   4 - Leave: Save all changes and exit.
```
