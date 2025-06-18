
# 🏦 MNW Banking System (Console-based C++ Project)

This is a simple banking system written in C++ that simulates basic teller functionalities, including client management and user authentication with permission handling.

---

## 📂 Features

### 🔐 Authentication System
- **Login & Sign-Up**
- Teller authentication using ID and password.
- Recommended password generation for new users.
- Full or custom access rights via a permission system.

### 👨‍💼 Teller Permissions
Tellers can be assigned specific permissions such as:
- View client list
- Add a new client
- Delete client
- Update client information
- Find client
- Perform transactions

Permissions are stored as an integer bitmask (e.g., `1` for view, `2` for add, etc.).

### 📋 Client Management
- View a list of all clients
- Add a new client with details
- Delete a client by account number
- Update client information
- Find a client by account number

### 💰 Transactions
- Deposit and withdrawal for any client by account number.
- Show all balances.

### 📁 File Storage
- All data (clients and bank tellers) is stored in files using custom delimiters.
- Files are parsed and serialized manually (no database used).

---

## 🛠 Technologies Used
- **C++** (Procedural style)
- **File handling**
- **Vectors and Structs**
- **Console I/O and UI coloring (using `system("color")`)**
- **Basic security (ID/password login with retry limit)**

---

## 🔧 How It Works

### Startup Flow
```bash
AuthenticationWindow() -> Login or Sign Up -> ShowMainMenuScreen() -> ChoiceImplement()
```

### File Handling
Files are used to persist:
- Teller data (`FileName2`)
- Client data (`FileName`)

Each line in the file is parsed using a `#//#` delimiter and loaded into memory as a vector of structs.

---

## 📜 Sample Permissions Mapping

| Action            | Bitmask Value |
|-------------------|---------------|
| Show Clients      | 1             |
| Add Client        | 2             |
| Delete Client     | 4             |
| Update Client     | 8             |
| Find Client       | 16            |
| Transactions      | 32            |

---

## 🧑‍💻 Functions Overview

### Authentication Functions
- `LoginWindow()`
- `LoginProcess()`
- `SignInWindow()`
- `SignInProcess()`
- `PermissionsCheck()`

### Core Menu Logic
- `ShowMainMenuScreen()`
- `ChoiceImplement()`
- `AuthenticationWindow()`
- `AuthenticationImplementation()`

### Client Functions
- `ShowClientList()`
- `AddClient()`
- `DeleteClient()`
- `UpdateClientInfo()`
- `FindClient()`

### Transactions
- `DepositMoney()`
- `WithdrawMoney()`
- `ShowAllBalances()`

---

## ▶ How to Run

1. Make sure you have a C++ compiler installed (e.g., `g++`).
2. Compile the code:
   ```bash
   g++ main.cpp -o BankSystem
   ```
3. Run the application:
   ```bash
   ./BankSystem
   ```

---

## 📝 Notes

- The program uses `system("cls")` and `system("color")`, so it’s intended for Windows console environments.
- No GUI or OOP concepts are used; this project is purely functional/procedural with text-based navigation.
- Ideal for learning file operations and access control in C++.
