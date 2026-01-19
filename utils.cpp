#ifndef UTILS_CPP
#define UTILS_CPP

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

#include "config.hpp"

void displayWelcomeMenu() {
    cout << "--------------------------" << endl;
    cout << "Welcome to the " << APP_NAME << "!" << endl;
    cout << "Please choose an option:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Other. Exit" << endl;
    cout << "--------------------------" << endl;
    cout << "Enter your choice: ";
}

void displayLoginMenu() {
    cout << "--------------------------" << endl;
    cout << "Login Menu" << endl;
    cout << "1. Reset Password" << endl;
    cout << "Other. Logout" << endl;
    cout << "--------------------------" << endl;
    cout << "Enter your choice: ";
}

//AI generated: Turn off echoing password on console, show * instead
std::string getHiddenPassword() {
    std::string password;
    char ch;
    
    while ((ch = _getch()) != '\r') {  // Read until Enter is pressed
        if (ch == '\b') {  // Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";  // Erase the asterisk
            }
        } else {
            password += ch;
            std::cout << '*';  // Display asterisk instead of character
        }
    }
    std::cout << std::endl;
    return password;
}
//End AI generated function

#endif // UTILS_CPP