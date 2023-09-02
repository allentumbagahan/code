#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
using namespace std;


int home();
void processSelection1(int);
void HorizontalLine();
void createAccount();
void login();
void customHeaderMessageWithLine(string, int);
void AccountOpen(int);

struct account{
    string username;
    int accountNumber;
    string email;
    string password;
    string pin;
    int balance;
};

vector<account> accounts;

int main(){

    while(1){
    int selected;
    // load the account from local file to vector
    accounts.clear();
    string stringInLine;
    fstream filestream1;
    filestream1.open("myGCST-ATM-ACCOUNTS.txt");
    if(!filestream1.fail()){
        while(!filestream1.eof()){
                getline(filestream1, stringInLine);
                    if (!stringInLine.empty()) {
                    account acc;  
                    stringstream ss(stringInLine);
                    ss >> acc.username >> acc.email >> acc.password >> acc.pin;
                    accounts.push_back(acc);  // Add the account to the vector
                }
            }
        filestream1.close();
    }
    selected = home();
    processSelection1(selected);
    }
    return 0;
}


int home(){
    int selected;
    customHeaderMessageWithLine("Welcome To GCST ATM Machine", 10);
    cout  << setfill(' ') << setw(10) << "" 
    << "A Bank is a place that will \n " << setw(2) << "" 
    << "ensure the safety and security of your money \n " ;
    thread td1 {[&](){ // & in bracket means all local variables
        cout  << endl <<  setfill(' ') << setw(8) << "";
        system("pause");
        customHeaderMessageWithLine("Welcome To GCST ATM Machine", 10);
        cout << "Choose what you want to do : \n"
        << " 1. Open an Account \n"
        << " 2. Log In Account \n"
        << " 3. Exit \n \n"
        << "Choose : ";
        cin >> selected;
        if(cin.fail()){
            cin.clear(); // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //  ignore any remaining characters in the input buffer
        }
        HorizontalLine();
    }};
    thread td2{[](){
        this_thread::sleep_for(50ms);
        HorizontalLine();
    }};
    td1.join();
    td2.join();
    return selected;
}

void HorizontalLine(){
    cout << endl << setfill('-') << setw(49) << "\n";
}

void processSelection1(int s) {
    if (s == 1) {
        createAccount();
    }else if(s == 2){
        login();
    }
    else {
        home();
    }
    
}
void customHeaderMessageWithLine(string msg, int halflinecount){
    cout  << endl << setfill('-') << setw(halflinecount) << " ";
    cout  << msg;
    cout  << " "<< setfill('-') << setw(halflinecount) << "" << endl << endl;
}

void createAccount(){  
        fstream filestream2;
        int accountRegistered = accounts.size();
        bool accountCreated = false;
        system("cls");
        while(!accountCreated){
            account creatingAccount = {"", 0, "", "", "", 0};
            string passwordConfirmation;
            bool uniqueEmail = false;
            customHeaderMessageWithLine("Create Your Account", 14);
            cout << "Enter Username : ";
            cin >> creatingAccount.username;
            cout << "Enter Email : ";
            cin >> creatingAccount.email;

            for(int a = 0; a < accountRegistered; a++){
                if(creatingAccount.email == accounts[a].email){
                    customHeaderMessageWithLine("Email is Already Registered", 10);
                    break;
                }else{
                    uniqueEmail = true;
                }
            }
            if(accountRegistered == 0){
                 uniqueEmail = true;
            }

            if(uniqueEmail){
                cout << "Enter Password : ";
                cin >> creatingAccount.password;
                cout << "Enter Confirm Password : ";
                cin >> passwordConfirmation;
                if(passwordConfirmation == creatingAccount.password){
                    cout << "Enter PIN (4-digit number) : ";
                    cin >> creatingAccount.pin;
                    if(creatingAccount.pin.size() == 4){
                        cout << "Enter Starting Balance : ";
                        cin >> creatingAccount.balance;
                        accountCreated = true;
                        customHeaderMessageWithLine("Account Created Successfully", 10);
                        customHeaderMessageWithLine("Review Your Account ", 12);

                        // Create a random number engine
                        random_device rd; // declare a random number generator using hardware entropy source
                        mt19937 gen(rd()); // generate random number engine using 32-bit Mersenne Twister 
                        int min  = 100000; // minimun range
                        int max = 999999; // maximum range
                        uniform_int_distribution<int> distribution(min, max); //Create a uniform distribution, produces integer values evenly distributed across a range
                        creatingAccount.accountNumber = distribution(gen); // generate random number using uniform distribution across a range

                        cout  << "ACOOUNT NUMBER : " << creatingAccount.accountNumber << endl;
                        cout  << "USERNAME : " << creatingAccount.username << endl;
                        cout  << "EMAIL : " << creatingAccount.email << endl;
                        cout  << "PASSWORD : " << creatingAccount.password << endl;
                        cout  << "PIN : " << creatingAccount.pin << endl << endl;
                        cout  << "Do not share this to anyone" << endl;
                        thread td3{[](){
                        this_thread::sleep_for(20ms);
                        HorizontalLine();
                        }};

                        // save created account
                        filestream2.open("myGCST-ATM-ACCOUNTS.txt", ios::out | ios::app);
                        filestream2 << creatingAccount.username << " " 
                                    << creatingAccount.accountNumber << " " 
                                    << creatingAccount.email << " " 
                                    << creatingAccount.password << " " 
                                    << creatingAccount.pin << " " 
                                    << creatingAccount.balance  << "\n";
                        filestream2.close();
                        system("pause");
                        td3.join();
                        system("cls");

                    }else{
                        customHeaderMessageWithLine("PIN must be a 4-digit number", 10);
                    }
                }else{
                    customHeaderMessageWithLine("Password Not Match", 14);
                }
            }
        }
}

void login(){
    system("cls");
    int InAccountNum;
    string InPin;
    int accountRegistered = accounts.size();
    bool accountLoggedOn = false;
    while(!accountLoggedOn){
        customHeaderMessageWithLine("Log In Account", 16);
        cout << "Enter Account Number : ";
        cin >> InAccountNum;
        cout << "Enter PIN : ";
        cin >> InPin;
        for(int a = 0; a < accountRegistered; a++){
            if(InAccountNum == accounts[a].accountNumber){
                if(InPin == accounts[a].pin){
                    accountLoggedOn = true;
                    thread td4{[](){
                    this_thread::sleep_for(20ms);
                    customHeaderMessageWithLine("Log In Successfully", 14);
                    }};
                    system("pause");
                    td4.join();
                    AccountOpen(a);
                }else{
                    customHeaderMessageWithLine("Incorrect PIN Number", 14);
                }
                break;
            }else{
                if(a == accountRegistered - 1){
                    customHeaderMessageWithLine("Account Not Found", 16);
                }
            }
        }
    }
}

void AccountOpen(int loggedOnAcc){
    int option;
    customHeaderMessageWithLine("Hi @" + accounts[loggedOnAcc].username + " welcome to GCST Atm Machine" , 5);
    cout << "1. Balance Inqury";
    cout << "2. Deposit";
    cout << "3. Widthraw";
    cout << "4. Fund Transfer";
    cout << "5. More Option ";
    cout << "6. Log Out ";
    thread td5{[](){
    this_thread::sleep_for(50ms);
    HorizontalLine();
    }};
    cout << "Choose Option : ";
    cin >> option;
    td5.join();
}