#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "config.hpp"
#include "hash.cpp"
#include "utils.cpp"

using namespace std;

class User {
private:
    string username;
    string password;

    bool isUsernameTooLong();

    bool isPasswordTooShort();

    bool isPasswordHasNumber();

    bool isPasswordHasSpecialChar();

public:
    User() {}

    string getUsername() const;

    string getHashPassword() const;

    friend istream& operator>>(istream& in, User& user);

    bool isUserExists();

    bool isPasswordStrong();

    void changePassword();

    void loginPage();

    void login();

    void registerUser();
    
    void clearCredentials();
};

#endif // USER_HPP