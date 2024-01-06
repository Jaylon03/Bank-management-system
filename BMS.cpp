
#include <iostream>
#include<iomanip>
#include<fstream>
#include<cctype>
#include<cstring>
#include <stdio.h>


using namespace std;

class Bank_Account {
    int account_number;
    char name[50];
    char type;
    int Money_Deposit;

public:
    void report() const;
    int retacno() const {
        return account_number;
    }
    void dep(int x){
        Money_Deposit+=x;
    }
    void draw(int x){
        Money_Deposit-=x;
    }
    int retdeposit() const{
        return Money_Deposit;
    }
    void modify();

    void create_account();

    void Display_Account();

};

void Bank_Account::report() const {
    cout << account_number << setw(10) << " " << name << setw(10) << type << setw(6) << Money_Deposit << endl;

}

void Bank_Account::modify(){
    cout<<"\t Account Number: "<<account_number<<endl;
    cout<<"\t Modify Account holder Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Modify Type of Acount: ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Modify Balance amount: ";
    cin>>Money_Deposit;

}


void write_account();
void display_details(int);
void delete_account(int);
void display_all();
void Money_deposit_withdraw(int, int);
void update_bank_account(int);





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
        cout << "\t 1. Create Account" << endl; // completed
        cout << "\t 2. Deposit Money" << endl; //completed/broken
        cout << "\t 3. Withdraw Money" << endl; // completed/broken
        cout << "\t 4.Balance Enquiry" << endl; // completed/works
        cout << "\t 5. All Account Holder List" << endl; //completed/works
        cout << "\t 6. Close an Account" << endl; // completed/Broken
        cout << "\t 7. Modify an Account" << endl; // completed/works
        cout << "\t 8. Exit" << endl;
        cout << endl;

        cout << "\t Enter your choice (1-8): ";
        cin >> choice;

        Bank_Account account;

        switch (choice) {
        case 1:
            write_account();  // create acount funtion
            break;
        case 2:
            system("cls");
            cout << "\t Enter Account number: ";  // deposit money function
            cin >> num;
            
            Money_deposit_withdraw(num, 1);

            break;
        case 3:
            system("cls");
            cout << "\t Enter Account number: "; // withdraw money function
            Money_deposit_withdraw(num, 2);

            cin >> num;
            break;
        case 4:

            cout << "\t Enter Account number: "; // display account function
            cin >> num;
            cout << endl;
            display_details(num);
         
            break;

            break;
        case 5:
            system("cls");                  // show all accounts function
            display_all();
           

            break;
        case 6:
            system("cls");
            cout << "\t Enter Account number: ";  // delete account function
            cin >> num;
            cout<<endl;
            delete_account(num);
            break;
        case 7:
            system("cls");
            cout << "\t Enter Account number: ";   //Modify account function
            cin >> num;
            update_bank_account(num);
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

void delete_account(int n) {// Works but is broken
    Bank_Account ac;
    ifstream inFile; //input file stream
    ofstream outFile; // output file stream
   
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any key...";
        return;
    }
    outFile.open("account_to_delete.dat", ios::binary);
    inFile.seekg(0, ios::beg);

    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Bank_Account)))
    {
        if (ac.retacno() == n) {
            outFile.write((char*)&ac, sizeof(ac)); 
        }
    }
    inFile.close();
    outFile.close();
    remove("account_to_delete.dat");
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
void display_all() {
    system("cls");
    Bank_Account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
       perror("File could not be open press !! any key...");
        return;
    }
    cout << "\t Bank Account holder List" << endl;
    cout << "============================================" << endl;
    cout << "A/c no.       NAME         TYPE  BALANCE" << endl;
    cout << "============================================" << endl;
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(Bank_Account))) {
        ac.report();
    }

}

void Money_deposit_withdraw(int n ,int option ) {
    int amt;
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("acount.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout << "File could not be found !! Press any key";
        return;
    }
     while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if(ac.retacno()==n){
            ac.Display_Account();
            if(option==1){
                cout << "Enter the amount of money you want to Deposit: ";
                cin>> amt;
                ac.dep(amt);
            }
            if(option == 2){
                cout<<"\t Enter the amount to be withdraw: ";
                cin>>amt;
                int Balance = ac.retdeposit() - amt;
                if(Balance < 0){
                    cout<<"\t Insufficient balance"<<endl;
                }
                else{
                    ac.draw(amt);
                }
            }
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account));
            File.seekp(pos,ios::cur); // move the pointer to the position of the file
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
            cout<<"\t Record Updated"<<endl;

            found = true;
        }
     }
     File.close();
     if(found == false){
        cout<<"\t Record Not Found"<<endl;
     }
}

void update_bank_account(int n){
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out); // opening file in binary mode
    if(!File){
        cout<<"File could not be found";
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)); // read record from file
        if(ac.retacno()==n){
            ac.Display_Account();
            cout<<endl;
            cout<<"\t Enter the new details of the account";
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account)); // move the pointer to the positon of the file
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
            cout<<"\t Record Updated"<< endl;
            found = true;

        }

    }
    File.close();
    if(found == false){
        cout<<"\t Record Not Found"<<endl;
    }
}