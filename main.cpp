// Login & Registration System

#include <windows.h>
#include <conio.h>
#include <iostream>

#include "user.hpp"
#include "user.cpp"

using namespace std;

int main() {
    displayWelcomeMenu();

    int choice;
    cin >> choice;
    
    if (choice == 1) 
    {
        cout << "Login selected." << endl;
        User user;
        user.login();

        main();
    }
    else if (choice == 2) 
    {
        cout << "Register selected." << endl;
        User user;
        user.registerUser();
        
        main();
    }

    return 0;
}
    