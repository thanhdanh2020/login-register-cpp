# Login & Registration System

A C++ console-based authentication system built for Windows using MinGW/g++. This project demonstrates fundamental concepts of user authentication, password security, and file-based data storage.

> ⚠️ **Notice**: This project is partially AI-generated. Some utility functions (e.g., `getHiddenPassword()`) were generated with AI assistance.

---

## 📁 Project Structure

```
login-register-system/
├── user/
│   └── data/
│       └── {username}.txt         # Per-user credential files
├── config.hpp                     # Global constants & messages
├── hash.cpp                       # Password hashing utility
├── utils.cpp                      # UI menus & password input
├── user.hpp                       # User class declaration
├── user.cpp                       # User class implementation
├── main.cpp                       # Application entry point
└── README.md                      # Project info
```

### File Descriptions

| File | Purpose |
|------|---------|
| `main.cpp` | Entry point with menu-driven UI (login/register/exit flow) |
| `user.hpp` | `User` class declaration with authentication methods |
| `user.cpp` | `User` class implementation (login, register, password reset) |
| `config.hpp` | Global constants (app name, validation rules, messages) |
| `hash.cpp` | Password hashing using `std::hash<string>` |
| `utils.cpp` | Windows-specific utilities (menus, masked password input) |

---

## 🔄 System Workflows

### 1. Registration Flow

```
┌─────────────────┐
│  Welcome Menu   │
│  [2] Register   │
└────────┬────────┘
         ▼
┌─────────────────┐
│ Enter Username  │
│ Enter Password  │
│ (masked input)  │
└────────┬────────┘
         ▼
┌─────────────────────┐
│  Validate Username: │
│  • User exists?     │ ─► Error: Username already exists
└────────┬────────────┘
         ▼
┌─────────────────────┐
│  Validate Password: │
│  • Length ≥ 6?      │ ─► Error: Password too short
│  • Has number?      │ ─► Error: Need numeric digit
│  • Has special?     │ ─► Error: Need special char
└────────┬────────────┘
         ▼
┌─────────────────┐
│ Save to file:   │
│ user/data/      │
│ {username}.txt  │
└────────┬────────┘
         | Success
         ▼
┌─────────────────┐
│   Return to     │
│  Welcome Menu   │
└─────────────────┘
```

### 2. Login Flow

```
┌─────────────────┐
│  Welcome Menu   │
│  [1] Login      │
└────────┬────────┘
         ▼
┌─────────────────┐
│ Enter Username  │
│ Enter Password  │
└────────┬────────┘
         ▼
┌─────────────────┐
│ Load user file  │
│ Compare hash    │
└────────┬────────┘
         │
    ┌────┴────┐
    │ Match?  │
    └────┬────┘
     Yes │  No
    ┌────┴────────────┐
    ▼                 ▼
┌─────────┐    ┌─────────────┐
│ Login   │    │ Login Failed│
│ Success │    │ Return Menu │
└────┬────┘    └─────────────┘
     ▼
┌─────────────────┐
│   Login Menu    │
│ [1] Reset Pass  │
│ [*] Logout      │
└─────────────────┘
```

### 3. Change Password Flow

```
┌─────────────────┐
│   Login Menu    │
│ [1] Change Pass │
└────────┬────────┘
         ▼
┌─────────────────┐
│ Enter New Pass  │
│ (masked input)  │
└────────┬────────┘
         ▼
┌─────────────────┐
│ Same as old?    │──── Yes ────┐
└────────┬────────┘             │
         │ No                   │
         ▼                      │
┌─────────────────┐             │
│Validate Password│             │
│  • Length ≥ 6?  │             │
│  • Has number?  │             │
│  • Has special? │             │
└────────┬────────┘             │
         │                      │
    Valid│  Invalid             │
    ┌────┴──────────────────────┤
    ▼                           ▼
┌─────────────┐          ┌─────────────┐
│ Update file │          │   Error!    │
│ Hash & Save │          │ Return to   │
└──────┬──────┘          │ Login Menu  │
       | Success         └─────────────┘
       ▼                 
┌─────────────────┐
│   Return to     │
│  Welcome Menu   │
└─────────────────┘
```

---

## 📚 Libraries Used

### C++ Standard Libraries

| Library | Purpose |
|---------|---------|
| `<iostream>` | Console input/output (`cin`, `cout`) |
| `<fstream>` | File operations (`ifstream`, `ofstream`) |
| `<string>` | String manipulation |
| `<functional>` | `std::hash` for password hashing |

### Windows-Specific Libraries

| Library | Purpose |
|---------|---------|
| `<windows.h>` | Windows API (included for compatibility) |
| `<conio.h>` | `_getch()` for reading single characters without echo |

---

## 🔐 Data Storage Format

User credentials are stored as individual text files in `user/data/`:

```
user/data/{username}.txt
├── Line 1: username (plain text)
└── Line 2: password (hashed numeric string)
```

**Example** (`user/data/john.txt`):
```
john
14695981039346656037
```

---

## 🌐 Reflection: Real-World Login Systems (REST API)

This console application demonstrates concepts that mirror real-world authentication systems:

| This Project | Real-World REST API Equivalent |
|--------------|--------------------------------|
| `user.login()` | `POST /api/auth/login` |
| `user.registerUser()` | `POST /api/auth/register` |
| `user.changePassword()` | `PUT /api/auth/password` |
| `checkUserExists()` | `GET /api/users/{username}/exists` |
| File-based storage | Database (MySQL, PostgreSQL, MongoDB) |
| `std::hash` | bcrypt, Argon2, PBKDF2 |
| Session in memory | JWT tokens, session cookies |

### API Request/Response Comparison

**Login - This Project:**
```cpp
// Input
cin >> username >> password;
// Process
if (storedHash == hashString(password)) { /* success */ }
```

**Login - REST API:**
```http
POST /api/auth/login
Content-Type: application/json

{
  "username": "john",
  "password": "myP@ssw0rd"
}

Response: 200 OK
{
  "token": "eyJhbGciOiJIUzI1NiIs...",
  "user": { "id": 1, "username": "john" }
}
```

---

## 🚀 Future Improvements

### 1. Single Sign-On (SSO)

Implement OAuth 2.0 / OpenID Connect for third-party authentication:

```
┌─────────────────┐
│  Login Options  │
├─────────────────┤
│ [1] Username    │
│ [2] Google SSO  │  ──► OAuth 2.0 flow
│ [3] GitHub SSO  │  ──► OAuth 2.0 flow
│ [4] Microsoft   │  ──► Azure AD
└─────────────────┘
```

**Benefits:**
- Users don't need to create new passwords
- Reduced password fatigue
- Enterprise integration (SAML, LDAP)

### 2. Passkey / WebAuthn (Passwordless)

Replace passwords with biometric/hardware authentication:

```
┌─────────────────────────────────────┐
│         Passkey Authentication       │
├─────────────────────────────────────┤
│  🔐 Use your device to sign in:     │
│                                      │
│  • Fingerprint                       │
│  • Face ID                           │
│  • Hardware Security Key (YubiKey)   │
│  • Windows Hello                     │
└─────────────────────────────────────┘
```

**Benefits:**
- Phishing-resistant (no password to steal)
- No password to remember
- Stronger security than passwords
- FIDO2 standard compliance

### 3. Additional Improvements

| Feature | Description |
|---------|-------------|
| **Multi-Factor Auth (MFA)** | TOTP codes, SMS verification |
| **Password Encryption** | Use bcrypt/Argon2 instead of `std::hash` |
| **Database Storage** | SQLite or MySQL instead of text files |
| **Rate Limiting** | Prevent brute-force attacks |
| **Session Management** | Token-based sessions with expiration |
| **Audit Logging** | Track login attempts and security events |

---

## 🛠️ Build & Run

### Prerequisites
- Windows OS
- MinGW g++ compiler (CodeBlocks installation)

### Build Command
```bash
g++ -fdiagnostics-color=always -g main.cpp -o main.exe
```

### Run
```bash
./main.exe
```

---

## 📝 License

This project is for educational purposes as part of the Fall 2025 C++ Programming course.

---

## 🤖 AI Assistance Disclosure

Parts of this project were developed with AI assistance:
- `getHiddenPassword()` function in `utils.cpp`
- Code review and optimization suggestions
- Documentation generation

Human review and testing were performed on all AI-generated code.
