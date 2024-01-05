
#include <iostream>
#include<iomanip>
#include<fstream>
#include<cctype>
#include<cstring>


using namespace std;

class Bank_Account {
    int account_number;
    char name[50];
    char type;
    int Money_Deposit;

public:
    int retacno() const {
        return account_number;
    }

    void create_account();

    void Display_Account();

};

void write_account();
void display_details(int);
void delete_account(int);

void Bank_Account::create_account() {
    system("cls");
    cout << "\t Enter the account number: ";
    cin >> account_number;
    cout << "\t Enter the name of the account holder: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\t Enter the type of the account (C/S): ";
    cin >> type;
    type = toupper(type);
    cout << "\t Enter the initial amount (>=500 for Saving and >= 1000 for current): ";
    cin >> Money_Deposit;
    cout << endl;
    cout << "\t Account Created.." << endl;
    cout << endl;
}

void Bank_Account::Display_Account() {
    cout << "\t Bank Account Number: " << account_number << endl;
    cout << "\t Account Holder Name: " << name << endl;
    cout << "\t Type of Account: " << type << endl;
    cout << "\t Balance amount: " << Money_Deposit << endl;
}






int main() {


    char ch;
    int num;


    do {
        int choice;
        cout << "\t\t ---------------------------------------" << endl;
        cout << "\t\t | Welcome to the Bank Management System |" << endl;
        cout << "\t\t ----------------------------------------" << endl;

        cout << endl;
        cout << "\t --- Main Menu --" << endl;
        cout << "\t 1. Create Account" << endl;
        cout << "\t 2. Deposit Money" << endl;
        cout << "\t 3. Withdraw Money" << endl;
        cout << "\t 4.Balance Enquiry" << endl;
        cout << "\t 5. All Account Holder List" << endl;
        cout << "\t 6. Close an Account" << endl;
        cout << "\t 7. Modify an Account" << endl;
        cout << "\t 8. Exit" << endl;
        cout << endl;

        cout << "\t Enter your choice (1-8): ";
        cin >> choice;

        Bank_Account account;

        switch (choice) {
        case 1:
            write_account();
            break;
        case 2:
            system("cls");
            cout << "\t Enter Account number: ";
            cin >> num;
            // Desposit function

            break;
        case 3:
            system("cls");
            cout << "\t Enter Account number: ";
            //Withdraw function
            cin >> num;
            break;
        case 4:

            cout << "\t Enter Account number: ";
            cin >> num;
            cout<<endl;
            display_details(num);
            // No need for additional input after displaying details
            break;

            break;
        case 5:
            system("cls");
            //display_all();
            //Account holder list function
            cin >> num;
            break;
        case 6:
            system("cls");
            cout << "\t Enter Account number: ";
            cin >> num;
            delete_account(num);

            // Close account function
            cin >> num;
            break;
        case 7:
            system("cls");
            cout << "\t Enter Account number: ";
            //Modify account function
            cin >> num;
            break;

        case 8:
            cout << "\t Exiting the program. Goodbye!" << endl;
            break;

        }

        cin.ignore();
        cin.get();
    } while (ch != '8');
        return 0;


}

void write_account()
{
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(Bank_Account));
    outFile.close();
}

void delete_account(int n) {
    Bank_Account ac;
    ifstream inFile; //input file stream
    ofstream outFile; // output file stream
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);

    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Bank_Account)))
    {
        if (ac.retacno() != n) {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(Bank_Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Bank_Account.dat");
    rename("Temp.dat", "Bank_Account.dat");
    cout << "\t Record Deleted... " << endl;

}

void display_details(int n) {
    Bank_Account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any key...";
        return;
    }
    cout << "\t Bank Account Details" << endl;
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Bank_Account)))
    {
        if (ac.retacno() == n) {
            ac.Display_Account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false) {
        cout << "\t Account number does not exist" << endl;
    }

}