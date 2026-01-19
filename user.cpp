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

    bool User::checkUserExists() 
    {
        ifstream file(USER_DATA_FOLDER + this->username + ".txt");
        return file.good();
    }

    void User::resetPassword()
    {
        cout << "Enter new password: ";
        string newPassword = getHiddenPassword();
        if (this->password == newPassword) {
            cout << MSG_ERROR_PASSWORD_SAME_AS_OLD << endl;
            this->loginPage();
        }
        this->password = newPassword;
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
            // Choice 1: Reset Password
            this->resetPassword();
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

        if (user == this->username && hashedPass == this->getHashPassword()) {
            this->loginPage();
        }
        else {
            this->clearCredentials();
            cout << MSG_ERROR_LOGIN_FAILED << endl;
        }
    }

    void User::registerUser()
    {
        cin >> *this;
        if (this->checkUserExists()) {
            cout << MSG_ERROR_USERNAME_EXISTS << endl;
            return;
        }

        if (PASSWORD_VALIDATION_ENABLED) {
            if (!isUsernameTooLong()) {
                cout << MSG_ERROR_USERNAME_TOO_LONG << endl;
                return;
            }
            if (!isPasswordTooShort()) {
                cout << MSG_ERROR_PASSWORD_TOO_SHORT << endl;
                return;
            }
            if (!isPasswordHasNumber()) {
                cout << MSG_ERROR_PASSWORD_REQUIRE_NUMBER << endl;
                return;
            }
            if (!isPasswordHasSpecialChar()) {
                cout << MSG_ERROR_PASSWORD_REQUIRE_SPECIAL << endl;
                return;
            }
        }

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
