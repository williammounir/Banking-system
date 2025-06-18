# 🏦 Console-Based Banking System in C++

This project is a **Bank Teller Management & Authentication System**, designed as a simple console-based application in C++. It allows bank tellers to register, log in, and access features based on their permissions.

---

## 📋 Features

- ✅ Bank Teller Sign-Up (with auto or custom password)
- ✅ Login with secure retry system (up to 4 attempts)
- ✅ Bitmask-based permission system
- ✅ Main menu navigation
- ✅ Color-coded interface for enhanced user experience
- ✅ Input validation and basic error handling

---

## 🧾 Main Functionalities

- **Authentication System**:
  - Sign up new bank tellers
  - Check for duplicate IDs
  - Login with retry logic
- **Permissions**:
  - Bitmask encoding for managing access to:
    - Show client list
    - Add/update/delete client
    - View transactions
- **Navigation**:
  - After login, user accesses the main menu
  - System is modular and supports further extensions

---

## 🛠️ Technologies

- Language: **C++**
- Libraries used:
  - `<iostream>`
  - `<vector>`
  - `<string>`
  - `<limits>`
  - `<ctime>`
  - (Assumed: custom helper functions for file handling like `ReadFileContent()`)

---

## 📁 Code

```cpp
// --- Main Menu Handling ---
case enMainMenuChoice::eExit:
    system("cls");
    AuthenticationWindow();
    break;

// --- Show Menu ---
void ShowMainMenuScreen(stBankTellersData banktellertocheck) {
    system("color 07");
    system("cls");
    cout << "==========================================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "==========================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Log Out.\n";
    cout << "==========================================================\n";
    cout << "Choose What Do you want to do? [1 to 7]?";

    short choice=0;
    choice = ReadIntNumberBetween(1, 7);
    ChoiceImplement(enMainMenuChoice(choice), banktellertocheck);
}

// --- Enums ---
enum eChosingAuth {
    eLogin = 1,
    eSignIn = 2,
    eExit2 = 3
};

// --- Login ---
bool LoginProcess(stBankTellersData &banktellertocheck) {
    string Id;
    vector<stBankTellersData> vbanktellersdata = ReadFileContent(FileName2, "#//#");

    cout << "Enter Id: ";
    getline(cin >> ws, Id);

    while (!checkBankTellersexistance(vbanktellersdata, banktellertocheck, Id)) {
        system("color E0");
        cout << "Id not found, please try again.\n";
        cout << "Enter Id: ";
        getline(cin >> ws, Id);
    }

    for (int i = 3; i >= 0; i--) {
        cout << "Enter Password: ";
        string pass;
        getline(cin >> ws, pass);

        if (pass == banktellertocheck.Password) {
            cout << "\n\t\t\tHELLO MASTER " << banktellertocheck.name << endl;
            system("color 27");
            cout << "please enter any key to continue\n";
            system("pause>0");
            return true;
        }

        if (i > 0)
            cout << "Wrong password, you have " << i << " tries left.\n";
    }

    return false;
}

// --- Login Window ---
void LoginWindow() {
    system("cls");
    cout << "\n-------------------------------------------\n";
    cout << "            LOGIN TO YOUR ACCOUNT\n";
    cout << "-------------------------------------------\n";
    stBankTellersData banktellertocheck;
    if (LoginProcess(banktellertocheck)) {
        ShowMainMenuScreen(banktellertocheck);
    } else {
        cout << "failed login!, try another time.\n";
    }
}

// --- Permissions ---
int PermissionsCheck() {
    int permissions = 0;
    char choice;
    cout << "Do You Want To give access to :\n\n";

    cout << "Show Client List? y/n? "; cin >> choice;
    if (tolower(choice) == 'y') permissions += 1;

    cout << "Add New Client? y/n? "; cin >> choice;
    if (tolower(choice) == 'y') permissions += 2;

    cout << "Delete Client? y/n? "; cin >> choice;
    if (tolower(choice) == 'y') permissions += 4;

    cout << "Update Client? y/n? "; cin >> choice;
    if (tolower(choice) == 'y') permissions += 8;

    cout << "Find Client? y/n? "; cin >> choice;
    if (tolower(choice) == 'y') permissions += 16;

    cout << "Transactions? y/n? "; cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (tolower(choice) == 'y') permissions += 32;

    return permissions;
}

// --- Sign Up Process ---
void SignInProcess() {
    stBankTellersData NewBankTeller;
    cout << "Enter Id: ";
    getline(cin >> ws, NewBankTeller.Id);

    vector<stBankTellersData> vbanktellers = ReadFileContent(FileName2, "#//#");
    while (checkBankTellersexistance(vbanktellers, NewBankTeller.Id)) {
        cout << "THE ID ALREADY EXISTS\n";
        cout << "Please enter another id\n";
        getline(cin >> ws, NewBankTeller.Id);
    }

    cout << "Enter Name: ";
    getline(cin, NewBankTeller.name);

    cout << "Enter Password <do you want us to recommend a password?> y/n ? : ";
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(choice) == 'y') {
        NewBankTeller.Password = GenerateKey(enCharType::MixChars);
        cout << "Your password is: " << NewBankTeller.Password << endl;
    } else {
        cout << "ENTER PASSWORD: ";
        getline(cin, NewBankTeller.Password);
    }

    cout << "Do You Want To Give Full Access? y/n ? ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (tolower(choice) == 'n') {
        NewBankTeller.Permissions = PermissionsCheck();
    }

    vbanktellers.push_back(NewBankTeller);
    cout << "\nYour registration was done successfully, thank you for your patience\n";
    AddBankTellersToFile(vbanktellers);

    cout << "\nPlease press any key to continue...\n";
    cin.get();
}

// --- Sign Up Window ---
void SignInWindow() {
    cout << "\n-------------------------------------------\n";
    cout << "            SIGN UP MENU\n";
    cout << "-------------------------------------------\n\n";
    SignInProcess();
}

// --- Authentication Logic ---
void AuthenticationImplementation(eChosingAuth eChoice) {
    if (eChoice == eChosingAuth::eLogin) {
        system("cls");
        LoginWindow();
    } else if (eChoice == eChosingAuth::eSignIn) {
        system("cls");
        SignInWindow();
        LoginWindow(); // Optional: prompt user to log in again
    } else if (eChoice == eChosingAuth::eExit2) {
        system("cls");
        programends();
    }
}

// --- Authentication Window ---
void AuthenticationWindow() {
    int choice;
    cout << "===========================================\n";
    cout << "         WELCOME TO MNW BANK SYSTEM\n";
    cout << "===========================================\n";
    cout << "    [1] Login\n";
    cout << "    [2] Sign up new bank teller\n";
    cout << "    [3] Exit\n";
    cout << "-------------------------------------------\n";
    cout << "Enter your choice: ";
    choice = ReadIntNumberBetween(1, 3);
    AuthenticationImplementation(eChosingAuth(choice));
}

// --- Main Entry ---
int main() {
    srand((unsigned)time(NULL));
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    AuthenticationWindow();
    system("pause>0");
    return 0;
}
