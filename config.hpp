#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

//App name
const std::string APP_NAME = "Login & Registration System";

//Username configurations
const int USERNAME_MAX_LENGTH = 20;

//Password configurations
const bool PASSWORD_VALIDATION_ENABLED = true; // Disable this will disable all password requirements checks below
const bool PASSWORD_REQUIRE_MIN_LENGTH = true;
const int PASSWORD_MIN_LENGTH = 6;
const bool PASSWORD_REQUIRE_SPECIAL = true;
const bool PASSWORD_REQUIRE_NUMBER = true;
const std::string PASSWORD_SPECIAL_CHARACTERS = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~";

//User data folder paths configurations
const std::string USER_DATA_FOLDER = "user/data/";

// Success message configurations
const std::string MSG_SUCCESS_REGISTRATION = "Registration successful! You can now log in with your credentials.";
const std::string MSG_SUCCESS_LOGIN = "Login successful! Welcome back, user ";
const std::string MSG_SUCCESS_LOGOUT = "You have been logged out successfully.";
const std::string MSG_SUCCESS_PASSWORD_RESET = "Password has been reset successfully. Please re-login with your new password.";

// Error message configurations
const std::string MSG_ERROR_USERNAME_TOO_LONG = "Error: Username exceeds maximum length of " + std::to_string(USERNAME_MAX_LENGTH) + " characters.";
const std::string MSG_ERROR_PASSWORD_TOO_SHORT = "Error: Password must be at least " + std::to_string(PASSWORD_MIN_LENGTH) + " characters long.";
const std::string MSG_ERROR_PASSWORD_REQUIRE_SPECIAL = "Error: Password must contain at least one special character";
const std::string MSG_ERROR_PASSWORD_REQUIRE_NUMBER = "Error: Password must contain at least one numeric digit (0-9).";
const std::string MSG_ERROR_PASSWORD_SAME_AS_OLD = "Error: New password cannot be the same as the old password.";
const std::string MSG_ERROR_USERNAME_EXISTS = "Error: Username already exists. Please choose a different username.";
const std::string MSG_ERROR_LOGIN_FAILED = "Login failed. Incorrect username or password.";

#endif // CONFIG_HPP


