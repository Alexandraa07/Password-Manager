cmake_minimum_required(VERSION 3.15)
project(PasswordManager CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(unofficial-sodium CONFIG REQUIRED)

include_directories(headers)

add_executable(password_manager
    src/main.cpp
    src/CryptoManager.cpp
    src/CredentialStorage.cpp
    src/PasswordEntry.cpp
    src/PasswordManager.cpp
)

target_link_libraries(password_manager PRIVATE unofficial-sodium::sodium)