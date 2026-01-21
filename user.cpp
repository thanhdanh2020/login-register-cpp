#ifndef USER_CPP
#define USER_CPP

#include "user.hpp"

    bool User::isUsernameTooLong() {
        return this->username.length() <= USERNAME_MAX_LENGTH;
    }

    bool User::isPasswordTooShort() {
        return this->password.length() >= PASSWORD_MIN_LENGTH;
    }

    bool User::isPasswordHasNumber() {
        for (char c : this->password) {
            if (isdigit(c)) {
                return true;
            }
        }
        return false;
    }
    bool User::isPasswordHasSpecialChar() {
        for (char c : this->password) {
            if (PASSWORD_SPECIAL_CHARACTERS.find(c) != string::npos) {
                return true;
            }
        }
        return false;
    }

    string User::getUsername() const
    {
        return username;
    }
    string User::getHashPassword() const
    {
        string hashedPass = hashString(password);
        return hashedPass;
    }
    
    istream& operator>>(istream& in, User& user)
    {
        cout << "Enter username: ";
        in >> user.username;
        cout << "Enter password: ";
        user.password = getHiddenPassword();
        return in;
    }

    bool User::isUserExists() 
    {
        ifstream file(USER_DATA_FOLDER + this->username + ".txt");
        return file.good();
    }

    bool User::isPasswordStrong() 
    {
        if (PASSWORD_VALIDATION_ENABLED)
        {
            return this->isPasswordHasNumber() &&
                   this->isPasswordHasSpecialChar() &&
                   this->isPasswordTooShort();
        }
        return true;
    }

    void User::changePassword()
    {
        // User enter new password
        cout << "Enter new password: ";
        string newPassword = getHiddenPassword();
        string oldPassword = this->password;

        // Conditions before 
        // If new password same as old password, show error and return to login page
        if (oldPassword == newPassword) {
            cout << MSG_ERROR_PASSWORD_SAME_AS_OLD << endl;
            this->loginPage();
            return;
        }

        // Set new password temporarily to check strength
        this->password = newPassword;
        // If new password not strong, show error and return to login page
        if (!this->isPasswordStrong()) {
            this->password = oldPassword; // Revert to old password
            cout << MSG_ERROR_PASSWORD_NOT_STRONG << endl;
            this->loginPage();
            return;
        }

        // Update password in user data file
        ofstream userFile;
        userFile.open(USER_DATA_FOLDER + this->username + ".txt");
        userFile << this->username << endl << this->getHashPassword() << endl;
        userFile.close();
        cout << MSG_SUCCESS_PASSWORD_RESET << endl;
    }

    void User::loginPage()
    {
        cout << MSG_SUCCESS_LOGIN << this->username << endl;
        displayLoginMenu();
        int choice;
        cin >> choice;
        if (choice == 1) {
            // Choice 1: Change Password
            this->changePassword();
        }
        else {
            // Choice Other: Logout
            this->clearCredentials();
            cout << MSG_SUCCESS_LOGOUT << endl;
        }
    }
    void User::login()
    {
        string user, hashedPass;
        cin >> *this;
        
        ifstream read(USER_DATA_FOLDER + this->username + ".txt");
        getline(read, user);
        getline(read, hashedPass);

        // Validate credentials
        // if correct username & password, process to login page
        if (user == this->username && hashedPass == this->getHashPassword()) {
            this->loginPage();
        }
        // else clear entered username & password, then show error message
        else {
            this->clearCredentials();
            cout << MSG_ERROR_LOGIN_FAILED << endl;
        }
    }

    void User::registerUser()
    {
        cin >> *this;
        // Conditions before register: 
        // Check if username exists, if true then show error message
        if (this->isUserExists()) {
            cout << MSG_ERROR_USERNAME_EXISTS << endl;
            return;
        }
        // Check if password strong, if false then show error message
        else if (!this->isPasswordStrong()) {
            cout << MSG_ERROR_PASSWORD_NOT_STRONG << endl;
            return;
        }

        // Pass all conditions, create user data file
        ofstream userFile;
        userFile.open(USER_DATA_FOLDER + this->username + ".txt");
        userFile << this->username << endl << this->getHashPassword() << endl;
        userFile.close();
        cout << MSG_SUCCESS_REGISTRATION << endl;
    }

    void User::clearCredentials()
    {
        this->username.clear();
        this->password.clear();
    }

#endif // USER_CPP
