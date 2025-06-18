
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<iomanip>
using namespace std;

const string FileName = "Clients.txt";
const string FileName2 = "banktellers2.txt";



struct stBankTellersData {

    string Id;
    string name;
    string Password;
    int Permissions = -1;

};

struct stclientdata {
    
    string AcountNumber;
    string PinCode;
    string ClientName;
    string Phone;
    int Balance;
    bool DeleteClient = false;
};

enum enMainMenuChoice {
    eShowClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactions = 6,
    eExit = 7
     

};

enum enCharType {
    SamallLetter = 1, CapitalLetter = 2,
    Digit = 3, MixChars = 4, SpecialCharacter = 5,
};

void ShowMainMenuScreen(stBankTellersData banktellertocheck);
void TransactionMainMenu(stBankTellersData banktellertocheck);


int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
{
    int Number;
    while (!(cin >> Number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ErrorMessage;
    }
    return Number;
}


bool IsNumberBetween(short Number, short From, short To)
{
    if (Number >= From && Number <= To)
        return true;
    else
        return false;
}


int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
{
    int Number = ReadIntNumber();

    while (!IsNumberBetween(Number, From, To))
    {
        cout << ErrorMessage;
        Number = ReadIntNumber();
    }
    return Number;
}

int RandomNumber(int From, int To)
{

    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

char GetRandomCharacter(enCharType CharType)
{


    if (CharType == MixChars)
    {
      
        CharType = (enCharType)RandomNumber(1, 3);

    }

    switch (CharType)
    {

    case enCharType::SamallLetter:
    {
        return char(RandomNumber(97, 122));
        break;
    }
    case enCharType::CapitalLetter:
    {
        return char(RandomNumber(65, 90));
        break;
    }
    case enCharType::SpecialCharacter:
    {
        return char(RandomNumber(33, 47));
        break; 
    }
    case enCharType::Digit:
    {
        return char(RandomNumber(48, 57));
        break;
    }
    
defualt:
    {
        return char(RandomNumber(65, 90));
        break;
    }
    }
}



string GenerateWord(enCharType CharType, short Length)

{
    string Word;

    for (int i = 1; i <= Length; i++)

    {

        Word = Word + GetRandomCharacter(CharType);

    }
    return Word;
}


string  GenerateKey(enCharType CharType = CapitalLetter)
{

    string Key = "";


    Key = GenerateWord(CharType, 4) + "-";
    Key = Key + GenerateWord(CharType, 4) + "-";
    Key = Key + GenerateWord(CharType, 4) + "-";
    Key = Key + GenerateWord(CharType, 4);


    return Key;
}


vector<string>SplitString(string record,string Delma) {

    vector<string>vstring;
    string s2 = "";
    int pos = 0;

    while ((pos = record.find(Delma)) != std::string::npos) {

        s2 = record.substr(0, pos);

        if (s2 != "") {
            vstring.push_back(s2);
        }

        record.erase(0, pos + Delma.length());


    }

    if (record != "") {
        vstring.push_back(record);
    }


    return vstring;

}








stclientdata ConvertLineIntoStructforclient(string record,string Delma) {

    vector<string>vrecord = SplitString(record, Delma);

    stclientdata client;

    client.AcountNumber = vrecord[0];
    client.PinCode = vrecord[1];
    client.ClientName = vrecord[2];
    client.Phone = vrecord[3];
    client.Balance = stoi(vrecord[4]);



    return client;


}

stBankTellersData ConvertLineIntoStructs(string record, string Delma) {

    vector<string>vrecord = SplitString(record, Delma);

    stBankTellersData BankTeller;

    BankTeller.Id = vrecord[0];
    BankTeller.name = vrecord[1];
    BankTeller.Password = vrecord[2];
    BankTeller.Permissions = stoi(vrecord[3]);
   



    return BankTeller;


}



vector<stclientdata> ReadFileContentForClient(string Filename,string Delma) {

    fstream myfile;
    vector<stclientdata>ClientsData;
    
    myfile.open(Filename, ios::in);


    if(myfile.is_open()){

        string line;

        while (getline(myfile, line)) {

            ClientsData.push_back(ConvertLineIntoStructforclient(line, Delma));

        }




        myfile.close();

    }

    return ClientsData;


}

vector<stBankTellersData> ReadFileContent(string Filename, string Delma) {

    fstream myfile;
    vector<stBankTellersData>BankTellersData;

    myfile.open(Filename, ios::in);


    if (myfile.is_open()) {

        string line;

        while (getline(myfile, line)) {

            if (!line.empty()) {
                BankTellersData.push_back(ConvertLineIntoStructs(line, Delma));
            }
        }




        myfile.close();

    }

    return BankTellersData;


}

void ViewClientsHeader(int NumberOfUsers) {


    cout << "\n\t\t\t\t\tClient List (" << NumberOfUsers << ") Client(s).\n\n";
    cout << "------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(15) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(15) << "Phone";
    cout << "| " << left << setw(18) << "Balance";
    cout << "\n------------------------------------------------------------------------------------------------------------------\n\n";

}

void ShowAllClients() {

    vector<stclientdata>VClientsData = ReadFileContentForClient(FileName,"#//#");

    ViewClientsHeader(VClientsData.size());

    if (VClientsData.size() != 0) {

        for (stclientdata Client : VClientsData) {

            cout << "| " << left << setw(20) << Client.AcountNumber;
            cout << "| " << left << setw(15) << Client.PinCode;
            cout << "| " << left << setw(40) << Client.ClientName;
            cout << "| " << left << setw(15) << Client.Phone;
            cout << "| " << left << setw(18) << Client.Balance<<"\n";
            
        }
        cout << "\n\n------------------------------------------------------------------------------------------------------------------\n\n";
    }
    else {
        cout << "\t\t\t\t\tTHERE IS NO CLIENTS IN THE SYSTEM";
        cout << "\n\n------------------------------------------------------------------------------------------------------------------\n\n";
    }

}




stclientdata ReadNewClient(vector<stclientdata>Vclientsdata) {
    stclientdata NewClient;

    cout << "Adding New Client:\n\n";
    cout << "Enter Account Number? ";
  
    bool repeated =  true;
    while (repeated) {
        getline(cin >> ws, NewClient.AcountNumber);
       

        for (stclientdata client : Vclientsdata) {
            if (client.AcountNumber == NewClient.AcountNumber) {
                cout << "Client with [" << NewClient.AcountNumber << "] already exists, Enter another Account Number? ";
                repeated = true;
                break;
            }
            else {
                repeated = false;
            }
           
            
        }

    }



    cout << "Enter PinCode? ";
    getline(cin >> ws, NewClient.PinCode);
    cout << "Enter Name? ";
    getline(cin >> ws, NewClient.ClientName);
    cout << "Enter Phone? ";
    getline(cin >> ws, NewClient.Phone);
    cout << "Enter AccountBalance? ";
    cin >> NewClient.Balance;
    
   

    return NewClient;


}

void AddClientstoFile(vector<stclientdata>Vclientsdata);

void AddNewClientScreen() {
    char choice;
    vector<stclientdata>Vclientsdata = ReadFileContentForClient(FileName,"#//#");
    cout << "\n------------------------------------------\n";
    cout << "\tAdd New Client Screen";
    cout << "\n------------------------------------------\n";
    do {
        
       
        Vclientsdata.push_back(ReadNewClient(Vclientsdata));
        
       
        cout << "Client add successfully, do you want to add more clients? Y/N? ";
        cin >> choice;
    } while (tolower(choice) == 'y');

    AddClientstoFile(Vclientsdata);
}

string ConvertRecordToLine(stclientdata client,string Delma) {

    string line="";

    line += client.AcountNumber + Delma;
    line += client.PinCode + Delma;
    line += client.ClientName + Delma;
    line += client.Phone + Delma;
    line += to_string(client.Balance) ;

    return line;


}

string ConvertRecordToLine(stBankTellersData bankteller, string Delma) {

    string line = "";

    line += bankteller.Id + Delma;
    line += bankteller.name + Delma;
    line += bankteller.Password+Delma ;
    line += to_string(bankteller.Permissions);
    
    

    return line;


}

bool checkclientexistance(vector<stclientdata>&vclientsdata, stclientdata &Clientcheck,string Accountnumber) {

    

    for (stclientdata &client : vclientsdata) {

        if (client.AcountNumber == Accountnumber) {
            Clientcheck = client;
      

            return true;
        }

    }

    return false;
}

bool checkBankTellersexistance(vector<stBankTellersData>& vbanktellersdata, stBankTellersData& banktellercheck, string Id) {



    for (stBankTellersData& bankteller : vbanktellersdata) {

        if (bankteller.Id == Id) {
            banktellercheck = bankteller;


            return true;
        }

    }

    return false;
}

bool checkBankTellersexistance(vector<stBankTellersData>& vbanktellersdata, string Id) {



    for (stBankTellersData& bankteller : vbanktellersdata) {

        if (bankteller.Id == Id) {
           


            return true;
        }

    }

    return false;
}

bool checkBankTellersexistancepass(vector<stBankTellersData>& vbanktellersdata, stBankTellersData& banktellercheck, string pass) {



    for (stBankTellersData& bankteller : vbanktellersdata) {

        if (bankteller.Password == pass) {
            banktellercheck = bankteller;


            return true;
        }

    }

    return false;
}

void MarkClientToDelete(vector<stclientdata>& vclientsdata,stclientdata clienttodelete) {


    for (stclientdata &client : vclientsdata) {
        if (client.AcountNumber == clienttodelete.AcountNumber) {
            client.DeleteClient = true;
            break;
        }
    }

}

void showclientdata(stclientdata client) {
    cout << "the following are the client details:\n";
    cout << "----------------------------------------------------\n";
    cout << "Account Number: " << client.AcountNumber << endl;
    cout  << "Pin Code: " << client.PinCode << endl;
    cout  << "Name: " << client.ClientName << endl;
    cout  << "Phone: " << client.Phone << endl;
    cout  << "Account Balance: " << client.Balance << endl;
    cout << "----------------------------------------------------\n\n";
}

void DeleteClientScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n------------------------------------------\n\n";

    vector<stclientdata>vclientsdata=ReadFileContentForClient(FileName,"#//#");
    cout << "Please enter AccountNumber? ";
    string Accountnumber;
    cin >> Accountnumber;
    stclientdata ClientToDelete;

    if (checkclientexistance(vclientsdata, ClientToDelete,Accountnumber)) {

        showclientdata(ClientToDelete);
        cout << "are you sure you want to delete this client? y/n ? ";
        char choice;
        cin >> choice;
        if (tolower(choice) == 'y') {
            MarkClientToDelete(vclientsdata, ClientToDelete);
            AddClientstoFile(vclientsdata);
            cout << "\n\nClient Deleted successfully.\n\n";
        }

    }
    else {
        cout << "\nclient with account number (" << Accountnumber << ") is not found!\n";
    }
    

    
}


void updateclient(vector<stclientdata>& vclientsdata,string accountnumber) {

    for (stclientdata &Client : vclientsdata) {

        if (Client.AcountNumber == accountnumber) {
            
            cout << "Enter PinCode? ";
            getline(cin >> ws, Client.PinCode);
            cout << "Enter Name? ";
            getline(cin >> ws, Client.ClientName);
            cout << "Enter Phone? ";
            getline(cin >> ws, Client.Phone);
            cout << "Enter AccountBalance? ";
            cin >> Client.Balance;
            cout << "client updated successfully!\n\n";
            break;
        }

    }

}


void UpdateClientScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n------------------------------------------\n\n";
    vector<stclientdata>vclientsdata = ReadFileContentForClient(FileName,"#//#");

    cout << "please enter account number? ";
    string accountnumber;
    cin >> accountnumber;
    stclientdata clienttoupdate;

    if (checkclientexistance(vclientsdata, clienttoupdate, accountnumber)) {
        showclientdata(clienttoupdate);
        cout << "Are you sure you want to update this client? y/n? ";
        char choice;
        cin >> choice;
        if (tolower(choice) == 'y') {
            updateclient(vclientsdata,accountnumber);
        }
    }
    else {
        cout << "\nclient with account number (" << accountnumber << ") is not found!\n";
    }

    AddClientstoFile(vclientsdata);

}

void findclientscreen() {

    cout << "\n------------------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n------------------------------------------\n\n";
    vector<stclientdata>vclientsdata = ReadFileContentForClient(FileName,"#//#");
    cout << "please enter account number? ";
    string accountnumber;
    cin >> accountnumber;
    stclientdata clienttoupdate;
    if (checkclientexistance(vclientsdata, clienttoupdate, accountnumber)) {
        showclientdata(clienttoupdate);
    }
    else {
        cout << "\nclient with account number (" << accountnumber << ") is not found!\n";
    }


}

enum enTransactionChoice {

    eDeposit=1,
    eWithdraw=2,
    eTotalBalances=3,
    eMainMenu=4


};

bool areyousure() {

    cout << "are you sure you want to make this transaction? y/n ? ";
    char choice;
    cin >> choice;

    if (tolower(choice) == 'y')
        return true;
    else
        return false;



}

void depositclient(vector<stclientdata>&vclientsdata,string accountnumber) {

    for (stclientdata &client : vclientsdata) {

        if (accountnumber == client.AcountNumber) {
            cout << "please enter deposit amount? ";
            int deposit;
            cin >> deposit;
            if (areyousure())
                client.Balance += deposit;

        }

    }
    AddClientstoFile(vclientsdata);

}


void withdrawclient(vector<stclientdata>& vclientsdata, string accountnumber) {

    for (stclientdata& client : vclientsdata) {

        if (accountnumber == client.AcountNumber) {
            
            
                cout << "please enter withdraw amount? ";
                int withdraw;
                cin >> withdraw;
                cout << endl;
                while (withdraw > client.Balance) {
                    cout << "Amount exceeds the balance, you can withdraw up to : " << client.Balance << endl;
                    cout << "please enter another amount? ";
                    cin >> withdraw;
                }
            if (areyousure())
                client.Balance -= withdraw;

        }

    }
    AddClientstoFile(vclientsdata);

}
void withdrawScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\withdraw Screen";
    cout << "\n------------------------------------------\n\n";
    vector<stclientdata>vclientsdata = ReadFileContentForClient(FileName,"#//#");
    cout << "please enter account number? ";
    string accountnumber;
    cin >> accountnumber;
    stclientdata clienttodeposit;
    if (checkclientexistance(vclientsdata, clienttodeposit, accountnumber)) {
        showclientdata(clienttodeposit);
        withdrawclient(vclientsdata, accountnumber);
    }
    else {
        cout << "\nclient with account number (" << accountnumber << ") is not found!\n";
    }

}


void DepositScreen() {
    cout << "\n------------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n------------------------------------------\n\n";
    vector<stclientdata>vclientsdata = ReadFileContentForClient(FileName,"#//#");
    cout << "please enter account number? ";
    string accountnumber;
    cin >> accountnumber;
    stclientdata clienttodeposit;
    if (checkclientexistance(vclientsdata, clienttodeposit, accountnumber)) {
        showclientdata(clienttodeposit);
        depositclient(vclientsdata, accountnumber);
    }
    else {
        cout << "\nclient with account number (" << accountnumber << ") is not found!\n";
    }

}

void ViewbalancesHeader(int NumberOfUsers) {


    cout << "\n\t\t\t\t\Balances List (" << NumberOfUsers << ") Client(s).\n\n";
    cout << "------------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(30) << "Balance";
    cout << "\n------------------------------------------------------------------------------------------------------------------\n\n";

}

void ShowAllbalances() {

    vector<stclientdata>VClientsData = ReadFileContentForClient(FileName,"#//#");

    ViewbalancesHeader(VClientsData.size());
    int sumbalances = 0;

    if (VClientsData.size() != 0) {

        for (stclientdata Client : VClientsData) {

            cout << "| " << left << setw(20) << Client.AcountNumber;
            cout << "| " << left << setw(40) << Client.ClientName;
            cout << "| " << left << setw(30) << Client.Balance << "\n";
            sumbalances += Client.Balance;
        }

        cout << "\n\n------------------------------------------------------------------------------------------------------------------\n\n";
        cout << "\t\t\t\t Total Balances = " << sumbalances << "\n\n";
    }
    else {
        cout << "\t\t\t\t\tTHERE IS NO CLIENTS IN THE SYSTEM";
        cout << "\n\n------------------------------------------------------------------------------------------------------------------\n\n";
        cout << "\t\t\t\t Total Balances = " << sumbalances << "\n\n";
    }

}


void RepeatTransactionScreen(stBankTellersData bankteller) {

    cout << "\nPress any key to go back to Transaction menu...";
    system("pause>0");
    TransactionMainMenu(bankteller);
   
}

void TransactionChoiceImplement(enTransactionChoice eChoice, stBankTellersData banktellertocheck) {

    switch (eChoice) {

    case enTransactionChoice::eDeposit:
        system("cls");
        DepositScreen();
        RepeatTransactionScreen(banktellertocheck);
        break;
    case enTransactionChoice::eWithdraw:
        system("cls");
        withdrawScreen();
        RepeatTransactionScreen(banktellertocheck);
        break;
    case enTransactionChoice::eTotalBalances:
        system("cls");
        ShowAllbalances();
        RepeatTransactionScreen(banktellertocheck);
        break;
    case enTransactionChoice::eMainMenu:
        system("cls");
        ShowMainMenuScreen(banktellertocheck);
        break;
    }

}

void TransactionMainMenu(stBankTellersData banktellertocheck) {

    system("cls");
    cout << "==========================================================\n";
    cout << "\t\tTransaction Menu Screen\n";
    cout << "==========================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "==========================================================\n";
    cout << "Choose What Do you want to do? [1 to 4]?";

    short choice = 0;
    
    choice = ReadIntNumberBetween(1, 4);


    TransactionChoiceImplement(enTransactionChoice(choice),banktellertocheck);

}



void AddClientstoFile(vector<stclientdata>Vclientsdata) {

  

    fstream myfile;
    myfile.open(FileName, ios::out);


    if (myfile.is_open()) {
        for (stclientdata client : Vclientsdata) {
           
            if (client.DeleteClient == false) {
                myfile << ConvertRecordToLine(client, "#//#") << "\n";
            }

        }
        myfile.close();
    }

}

void AddBankTellersToFile(vector<stBankTellersData>Vbanktellersdata) {



    fstream myfile;
    myfile.open(FileName2, ios::out);


    if (myfile.is_open()) {
        for (stBankTellersData bankteller : Vbanktellersdata) {

            
                myfile << ConvertRecordToLine(bankteller ,"#//#") << "\n";
           

        }
        myfile.close();
    }

}

void programends() {
    cout << "\n------------------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n------------------------------------------\n\n";

}




void RepeatMainMenu(stBankTellersData banktellertocheck) {
    cout << "\nPress any key to go back to main menu...";
    system("pause>0");
    ShowMainMenuScreen( banktellertocheck);
}

void AuthenticationWindow();



void ChoiceImplement(enMainMenuChoice eChoice, stBankTellersData banktellertocheck) {



    switch (eChoice) {

    case enMainMenuChoice::eShowClients:
        if (banktellertocheck.Permissions & (1 << 0)) {
            system("cls");
            ShowAllClients();
            RepeatMainMenu(banktellertocheck);
        }
        else {
            system("cls");
            cout << "\n-------------------------------------------------\n";
            cout << "Access Denied\n";
            cout << "You don't have the permission to do this,\n";
            cout << "Please contact your Admin.\n";
            cout << "\n-------------------------------------------------\n";
            RepeatMainMenu(banktellertocheck);
        }
        break;
    case enMainMenuChoice::eAddNewClient:
        if (banktellertocheck.Permissions & (1 << 1)) {
            system("cls");
            AddNewClientScreen();
            RepeatMainMenu(banktellertocheck);
        }
        else {
            system("cls");
            cout << "\n-------------------------------------------------\n";
            cout << "Access Denied\n";
            cout << "You don't have the permission to do this,\n";
            cout << "Please contact your Admin.\n";
            cout << "\n-------------------------------------------------\n";
            RepeatMainMenu(banktellertocheck);
        }
        break;
    case enMainMenuChoice::eDeleteClient:
        if (banktellertocheck.Permissions & (1 << 2)) {
            system("cls");
            DeleteClientScreen();
            RepeatMainMenu(banktellertocheck);
        }
        else {
            system("cls");
            cout << "\n-------------------------------------------------\n";
            cout << "Access Denied\n";
            cout << "You don't have the permission to do this,\n";
            cout << "Please contact your Admin.\n";
            cout << "\n-------------------------------------------------\n";
            RepeatMainMenu(banktellertocheck);
        }
        break;
    case enMainMenuChoice::eUpdateClient:
        if (banktellertocheck.Permissions & (1 << 3)) {
        system("cls");
        UpdateClientScreen();
        RepeatMainMenu(banktellertocheck);
        }
         else {
            system("cls");
            cout << "\n-------------------------------------------------\n";
            cout << "Access Denied\n";
            cout << "You don't have the permission to do this,\n";
            cout << "Please contact your Admin.\n";
            cout << "\n-------------------------------------------------\n";
            RepeatMainMenu(banktellertocheck);
        }
        break;
    case enMainMenuChoice:: eFindClient:
        if (banktellertocheck.Permissions & (1 << 4)) {
            system("cls");
            findclientscreen();
            RepeatMainMenu(banktellertocheck);
        }
        else {
            system("cls");
            cout << "\n-------------------------------------------------\n";
            cout << "Access Denied\n";
            cout << "You don't have the permission to do this,\n";
            cout << "Please contact your Admin.\n";
            cout << "\n-------------------------------------------------\n";
            RepeatMainMenu(banktellertocheck);
        }
        break;
    case enMainMenuChoice::eTransactions:
        if (banktellertocheck.Permissions & (1 << 5)) {
            system("cls");
            TransactionMainMenu(banktellertocheck);
            RepeatMainMenu(banktellertocheck);
        }
         else {
            system("cls");
            cout << "\n-------------------------------------------------\n";
            cout << "Access Denied\n";
            cout << "You don't have the permission to do this,\n";
            cout << "Please contact your Admin.\n";
            cout << "\n-------------------------------------------------\n";
            RepeatMainMenu(banktellertocheck);
            }
        break;
    case enMainMenuChoice:: eExit:
        system("cls");
        AuthenticationWindow();
        break;
    }

    






}




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

    
   

    ChoiceImplement(enMainMenuChoice(choice),banktellertocheck);

}


enum eChosingAuth {
    eLogin = 1,
    eSignIn=2,
    eExit2 = 3
};

bool LoginProcess(stBankTellersData &banktellertocheck) {

    string Id;

    vector<stBankTellersData>vbanktellersdata=ReadFileContent(FileName2,"#//#");


   
    cout << "Enter Id: ";
    getline(cin >> ws, Id);
      

    while (!checkBankTellersexistance(vbanktellersdata, banktellertocheck, Id)) {
        system("color E0");
        cout << "Id not founded,please try again.\n";
        cout << "Enter Id: ";
        getline(cin >> ws, Id);

    }

 

    cout << "Enter Password: ";
    string pass;
    getline(cin >> ws, pass);
    bool found = false;
    if (pass == banktellertocheck.Password) {
        cout << "\t\tHELLO MASTER " << banktellertocheck.name << endl;
        system("color 27");
        cout << "please enter any key to transfer to main menu\n";
        cin.get();
        return  true;
    }
    for (int i = 3; i >= 1; i--) {
        system("color 4F");
        cout << "\a";
        cout << "wrong password,please try again->you only have "<< i << " more tries\n";

        cout << "Enter Password: ";
        string pass;
        getline(cin >> ws, pass);
        if (pass == banktellertocheck.Password) {
            cout << "\n\t\t\tHELLO MASTER " << banktellertocheck.name << endl;
            system("color 27");
            cout << "please enter any key to continoue\n";
            system("pause>0");

            return  true;
        }
   }

    return false;


}

void LoginWindow() {

    system("cls");

    cout << "\n-------------------------------------------\n";
    cout << "            LOGIN TO YOUR ACCOUNT\n";
    cout << "-------------------------------------------\n";
    stBankTellersData banktellertocheck;
    if (LoginProcess(banktellertocheck)) {
        
        
        ShowMainMenuScreen( banktellertocheck);
    }
    else {
        
        cout << "failed login!, try another time.\n";
    }
  





}

int PermissionsCheck() {
    int permissions = 0;
    char choice;
    cout << "Do You Want To give access to :\n\n";
   
    cout << "Show Client List? y/n? ";
    cin >> choice;
    if (tolower(choice) == 'y')
        permissions += 1;
    
    cout << "Add New Client? y/n? ";
    cin >> choice;
    if (tolower(choice) == 'y')
        permissions += 2;


    cout << "Delete Client? y/n? ";
    cin >> choice;
    if (tolower(choice) == 'y')
        permissions += 4;

    cout << "Update Client? y/n? ";
    cin >> choice;
    if (tolower(choice) == 'y')
        permissions += 8;

    cout << "Find Client? y/n? ";
    cin >> choice;
    if (tolower(choice) == 'y')
        permissions += 16;

    cout << "Transactions? y/n? ";
    cin >>choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (tolower(choice) == 'y')
        permissions += 32;



    return permissions;

}


void SignInProcess() {
    stBankTellersData NewBankTeller;
    cout << "Enter Id: ";
    getline(cin >> ws, NewBankTeller.Id);

    vector<stBankTellersData> vbanktellers = ReadFileContent(FileName2, "#//#");
    while (checkBankTellersexistance(vbanktellers, NewBankTeller.Id)) {
        cout << "THE ID ALREADY EXISTS\n";
        cout << "Please enter another id\n";
        cout << "ENTER ID: ";
        getline(cin >>ws, NewBankTeller.Id);
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
    }
    else {
        cout << "ENTER PASSWORD: ";
        getline(cin, NewBankTeller.Password);
    }

    cout << "Do You Want To Give Full Access? y/n ?";
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



void SignInWindow() {

    cout << "\n-------------------------------------------\n";
    cout << "            SIGN UP MENU\n";
    cout << "-------------------------------------------\n\n";

    SignInProcess();



}

void AuthenticationImplementation(eChosingAuth eChoice) {

    if (eChoice==eChosingAuth::eLogin) {
        
        system("cls");

        LoginWindow();

    }
    else if(eChoice==eChosingAuth::eSignIn) {

        system("cls");

        SignInWindow();

        LoginWindow();
        

    }
    else if (eChoice == eChosingAuth::eExit2) {
        system("cls");
        programends();
    }



}

void AuthenticationWindow() {
    int choice;

    cout << "===========================================\n";
    cout << "         WELCOME TO MNW BANK SYSTEM\n";
    cout << "===========================================\n";
    cout << "    [1] Login\n";
    cout << "    [2] sign up new bank teller\n";
    cout << "    [3] Exit\n";
    cout << "-------------------------------------------\n";
    cout << "Enter your choice: ";
    
    choice = ReadIntNumberBetween(1, 3);

    AuthenticationImplementation(eChosingAuth(choice));


}





int main()
{
    srand((unsigned)time(NULL));

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

   

    
   

    AuthenticationWindow();
    
   

    system("pause>0");
    return 0;
}

