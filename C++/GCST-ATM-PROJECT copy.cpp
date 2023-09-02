#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <functional>
#include <cctype>
#include <chrono>
using namespace std;

int home();
void processSelection(int, const vector<function<void()>>);
void HorizontalLine();
void createAccount();
void login();
void customHeaderMessageWithLine(string, int);
void AccountOpen();
void balanceInquiry();
void deposit();
void withdraw();
void fundTransfer();
void transHistory();
void logOut();
long long getIntegerInput();
long long int generateReferenceNumber();
long long int getInputWithDataValidatorForInt(istream&, const string);

struct account{
    string username;
    long long int accountNumber;
    string email;
    string pin;
    int balance;
};

vector<account> accounts;
vector<string> transactionHistory;
int loggedOnAccIndex;
bool isloggedOut = false;
int maxWidth = 57;
chrono::milliseconds delay = 50ms;

int main(){

    while(1){
        int selected;
        // load the account from local file to vector
        accounts.clear();
        string stringInLine;
        fstream filestream1;
        vector<function<void()>> selection1Functions = {createAccount, login, home}; // list of function selection to be executed
        filestream1.open("myGCST-ATM-ACCOUNTS.txt");
        if(!filestream1.fail()){
            while(!filestream1.eof()){
                    getline(filestream1, stringInLine);
                        if (!stringInLine.empty()) {
                        account acc;  
                        stringstream ss(stringInLine);
                        ss >> acc.username >> acc.accountNumber >>  acc.email >> acc.pin >> acc.balance;
                        accounts.push_back(acc);  // Add the account to the vector
                    }
                }
            filestream1.close();
        }
        selected = home();
        if(!cin.fail()){
            if(selected > 0 && selected < 4){
                processSelection(selected, selection1Functions);
            }
        }else{
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    return 0;
}


int home(){
    int selected;
    system("cls");
    customHeaderMessageWithLine("Welcome To GCST ATM Machine", maxWidth);
    cout  << setfill(' ') << setw(10) << "" 
    << "A Bank is a place that will \n " << setw(2) << "" 
    << "ensure the safety and security of your money \n " ;
    thread td1 {[&](){ // & in bracket means all local variables
        cout  << endl <<  setfill(' ') << setw(8) << "";
        system("pause");
        customHeaderMessageWithLine("Welcome To GCST ATM Machine", maxWidth);
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
        this_thread::sleep_for(delay);
        HorizontalLine();
    }};
    td1.join();
    td2.join();
    return selected;
}

void HorizontalLine(){
    cout << endl << setfill('-') << setw(maxWidth + 3 ) << "\n";
}

void processSelection(int s, const vector<function<void()>> func) {
    func[s - 1]();
}
void customHeaderMessageWithLine(string msg, int maxWidth){
    int halflinecount = (maxWidth - msg.size())/2;
    cout  << endl << setfill('-') << setw(halflinecount + 1) << " ";
    cout  << msg;
    if(((maxWidth - msg.size()) % 2 == 1) ){
        cout  << " "<< setfill('-') << setw(halflinecount + 1) << "" << endl << endl;
    }else{
        cout  << " "<< setfill('-') << setw(halflinecount) << "" << endl << endl;
    }
}


void createAccount(){  
        fstream filestream2;
        int accountRegistered = accounts.size();
        bool accountCreated = false;
        system("cls");
        while(!accountCreated){
            account creatingAccount = {"", 0, "", "", 0};
            string passwordConfirmation;
            bool uniqueEmail = false;
            customHeaderMessageWithLine("Create Your Account", maxWidth);
            cout << "Enter Username : ";
            cin >> creatingAccount.username;
            cout << "Enter Email : ";
            cin >> creatingAccount.email;

            for(int a = 0; a < accountRegistered; a++){
                if(creatingAccount.email == accounts[a].email){
                    customHeaderMessageWithLine("Email is Already Registered", maxWidth);
                    uniqueEmail = false;
                    break;
                }else{
                    uniqueEmail = true;
                }
            }
            if(accountRegistered == 0){
                 uniqueEmail = true;
            }

            if(uniqueEmail){
                cout << "Enter PIN (6-digit number) : ";
                cin >> creatingAccount.pin;
                for(int c = 0; c < creatingAccount.pin.size(); c++){
                    if(!(creatingAccount.pin[c] > 47 && creatingAccount.pin[c] < 58)){
                        creatingAccount.pin = "";
                        customHeaderMessageWithLine("PIN must not have any character", maxWidth);
                        break;
                    }
                }
                if(creatingAccount.pin.size() == 6){
                    cout << "Enter Starting Balance : ";
                    creatingAccount.balance = getInputWithDataValidatorForInt(cin, "Invalid Starting Amount");
                    if(creatingAccount.balance > -1){
                        accountCreated = true;
                        customHeaderMessageWithLine("Account Created Successfully", maxWidth);
                        customHeaderMessageWithLine("Review Your Account ", maxWidth);

                        // Create a random number engine
                        random_device rd; // declare a random number generator using hardware entropy source
                        mt19937 gen(rd()); // generate random number engine using 32-bit Mersenne Twister 
                        long long int min  = 100000000; // minimun range
                        long long int max = 999999999;   // maximum range
                        uniform_int_distribution<int> distribution(min, max); //Create a uniform distribution, produces integer values evenly distributed across a range
                        creatingAccount.accountNumber = distribution(gen); // generate random number using uniform distribution across a range

                        cout  << "ACOOUNT NUMBER : " << creatingAccount.accountNumber << endl;
                        cout  << "USERNAME : " << creatingAccount.username << endl;
                        cout  << "EMAIL : " << creatingAccount.email << endl;
                        cout  << "PIN : " << creatingAccount.pin << endl << endl;
                        cout  << "Do not share this to anyone" << endl;
                        thread td3{[](){
                        this_thread::sleep_for(delay);
                        HorizontalLine();
                        }};

                        // save created account
                        filestream2.open("myGCST-ATM-ACCOUNTS.txt", ios::out | ios::app);
                        filestream2 << creatingAccount.username << " " 
                                    << creatingAccount.accountNumber << " " 
                                    << creatingAccount.email << " " 
                                    << creatingAccount.pin << " " 
                                    << creatingAccount.balance  << "\n";
                        filestream2.close();
                        system("pause");
                        td3.join();
                        system("cls");
                    }

                }else{
                    customHeaderMessageWithLine("PIN must be a 6-digit number", maxWidth);
                }
            }
        }
}
void login(){
    int accountRegistered = accounts.size();
    bool accountLoggedOn = false;
    system("cls");
    while(!accountLoggedOn){
        int InAccountNum;
        string InPin;
        customHeaderMessageWithLine("Log In Account", maxWidth);
        cout << "Enter Account Number : ";
        InAccountNum = getIntegerInput();
        cout << "Enter PIN : ";
        cin >> InPin;
        for(int a = 0; a < accountRegistered; a++){
            if(InAccountNum == accounts[a].accountNumber){
                if(InPin == accounts[a].pin){
                    accountLoggedOn = true;
                    thread td4{[](){
                    this_thread::sleep_for(delay);
                    customHeaderMessageWithLine("Log In Successfully", maxWidth);
                    }};
                    system("pause");
                    td4.join();
                    loggedOnAccIndex = a;
                    AccountOpen();
                }else{
                    customHeaderMessageWithLine("Incorrect PIN Number", maxWidth);
                }
                break;
            }else{
                if(a == accountRegistered - 1){
                    customHeaderMessageWithLine("Account Not Found", maxWidth);
                }
            }
        }
    }
}

void AccountOpen(){
    int option;
    isloggedOut = false;
    system("cls");
    while(!isloggedOut){
        vector<function<void()>> selection2Functions = {balanceInquiry, deposit, withdraw, fundTransfer, transHistory, logOut}; 
        customHeaderMessageWithLine("Hi @" + accounts[loggedOnAccIndex].username + " " , maxWidth);
        cout  << setfill(' ') << setw(8) << "" << " Welcome to GCST Atm Machine " << endl;
        cout  << setfill(' ') << setw(6) << "" << " Choose option you want to perform " << endl;
        cout << "1. Balance Inqury" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Widthraw" << endl;
        cout << "4. Fund Transfer" << endl;
        cout << "5. Transaction History "<< endl ;
        cout << "6. Log Out "<< endl ;
        cout << "Choose Option : ";
        cin >> option;
        if(!cin.fail() && option > 0 && option < 7){
            HorizontalLine();
            processSelection(option, selection2Functions);
        }else{
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            HorizontalLine();
        }
    }
}

void balanceInquiry(){
    system("cls");
    customHeaderMessageWithLine("Balance Inquiry" , maxWidth);
    cout << "Hi @" << accounts[loggedOnAccIndex].username << " your current balance is " << accounts[loggedOnAccIndex].balance << endl;
    thread td5{[](){
        this_thread::sleep_for(delay);
        HorizontalLine();
    }};
    system("pause");
    td5.join();
    system("cls");
}

void deposit(){
    bool isDepositSuccessful = false;
    int accountRegistered = accounts.size();
    string stringInLine;
    fstream filestream1;
    fstream filestream2;
    long double depositAmount;
    system("cls");
    while(!isDepositSuccessful){
        customHeaderMessageWithLine(" Deposit " , maxWidth);
        cout << "Enter Amount to Deposit : " ;
        depositAmount = getIntegerInput();
        if(depositAmount > 0){
                string pinNumber;
                bool validPIN = false;
                cout << "Enter PIN Number :";
                cin >> pinNumber;
                // validate pin
                for(int a = 0; a < accountRegistered; a++){
                    if(pinNumber == accounts[a].pin){
                        validPIN = true;
                        break;
                    }
                }
                if(validPIN){
                    accounts[loggedOnAccIndex].balance += depositAmount;
                    filestream1.open("myGCST-ATM-ACCOUNTS.txt", ios::out | ios::trunc);
                    if(!filestream1.fail()){
                        for(int acc = 0; acc < accountRegistered; acc++){
                                filestream1 << accounts[acc].username << " " 
                                            << accounts[acc].accountNumber << " " 
                                            <<  accounts[acc].email << " " 
                                            << accounts[acc].pin << " " 
                                            << accounts[acc].balance << "\n";
                        }
                    }
                    filestream1.close();
                    filestream2.open("myGCST-ATM-Transaction" + to_string(accounts[loggedOnAccIndex].accountNumber) + ".txt", ios::out | ios::app);
                    filestream2 << accounts[loggedOnAccIndex].accountNumber 
                                << " deposit with amount of "
                                << depositAmount << " Ref : "
                                << generateReferenceNumber()
                                << endl;
                    filestream2.close();                    
                    thread td6{[](){
                        this_thread::sleep_for(delay);
                        customHeaderMessageWithLine(" Deposit Successful ", maxWidth);
                    }};
                    system("pause");
                    isDepositSuccessful = true;
                    td6.join();
                    system("cls");
                }else{
                    customHeaderMessageWithLine(" Invalid PIN Number ", maxWidth);
                }
        }else{
            customHeaderMessageWithLine(" Deposit  Amount must be higher than 0 " , maxWidth);
        }
    }
}

void withdraw(){
    bool isWithdrawSuccessful = false;
    int accountRegistered = accounts.size();
    string stringInLine;
    fstream filestream1;
    fstream filestream2;
    long double withdrawAmount;
    system("cls");
    while(!isWithdrawSuccessful){
        customHeaderMessageWithLine(" Funds Withdrawal " , maxWidth);
        cout << "Enter Amount to Withdrawn : " ;
        withdrawAmount = getIntegerInput();
        if(withdrawAmount > 0){
            if(withdrawAmount < accounts[loggedOnAccIndex].balance){
                string pinNumber;
                bool validPIN = false;
                cout << "Enter PIN Number :";
                cin >> pinNumber;
                // validate pin
                for(int a = 0; a < accountRegistered; a++){
                    if(pinNumber == accounts[a].pin){
                        validPIN = true;
                        break;
                    }
                }
                if(validPIN){
                    accounts[loggedOnAccIndex].balance -= withdrawAmount;
                    filestream1.open("myGCST-ATM-ACCOUNTS.txt", ios::out | ios::trunc);
                    if(!filestream1.fail()){
                        for(int acc = 0; acc < accountRegistered; acc++){
                                filestream1 << accounts[acc].username << " " 
                                            << accounts[acc].accountNumber << " " 
                                            <<  accounts[acc].email << " " 
                                            << accounts[acc].pin << " " 
                                            << accounts[acc].balance << "\n";
                        }
                    }
                    filestream1.close();
                    filestream2.open("myGCST-ATM-Transaction" + to_string(accounts[loggedOnAccIndex].accountNumber) + ".txt", ios::out | ios::app);
                    filestream2 << accounts[loggedOnAccIndex].accountNumber 
                                << " widthraw with amount of "
                                << withdrawAmount << " Ref : "
                                << generateReferenceNumber()
                                << endl;
                    filestream2.close();
                    thread td6{[](){
                        this_thread::sleep_for(delay);
                        customHeaderMessageWithLine(" Withdrawal Successful ", maxWidth);
                    }};
                    system("pause");
                    isWithdrawSuccessful = true;
                    td6.join();
                    system("cls");                        
                }else{
                    customHeaderMessageWithLine(" Invalid PIN Number ", maxWidth);
                }                
            }else{
                customHeaderMessageWithLine(" Insufficient Balance " , maxWidth);
            }
        }else{
            customHeaderMessageWithLine(" Withdraw Amount must be higher than 0 " , maxWidth);
        }
    }
}


void fundTransfer(){
    bool isTransferSuccessful = false;
    bool isValidReceiverAccount = false;
    int accountRegistered = accounts.size();
    string stringInLine;
    fstream filestream1;
    fstream filestream2;
    int transferAmount;
    long long receiverAccountNumber;
    int receiverAccountIndex;
    system("cls");
    while(!isTransferSuccessful){
        customHeaderMessageWithLine(" Funds Transfer " , maxWidth);
        cout << "Enter Amount to Transfer : " ;
        transferAmount = getIntegerInput();
        if(transferAmount > 0){    
            cout << "Enter Receiver Account Number : " ;
            receiverAccountNumber = getIntegerInput();
            // validate receiver
            if(receiverAccountNumber > 99999999 && 999999999){
                for(int a = 0; a < accountRegistered; a++){
                    if(receiverAccountNumber == accounts[a].accountNumber){
                        isValidReceiverAccount = true;
                        receiverAccountIndex = a;
                        break;
                    }
                }


                if(accounts[loggedOnAccIndex].accountNumber == accounts[receiverAccountIndex].accountNumber){
                    customHeaderMessageWithLine(" Transfer Failed " , maxWidth);
                    isValidReceiverAccount = false;
                }
                if(isValidReceiverAccount){
                    if(transferAmount > 0){
                        if(transferAmount < accounts[loggedOnAccIndex].balance){
                            string pinNumber;
                            bool validPIN = false;
                            cout << "Enter PIN Number :";
                            cin >> pinNumber;
                            // validate pin
                            for(int a = 0; a < accountRegistered; a++){
                                if(pinNumber == accounts[a].pin){
                                    validPIN = true;
                                    break;
                                }
                            }
                            if(validPIN){
                                accounts[loggedOnAccIndex].balance -= transferAmount;
                                accounts[receiverAccountIndex].balance += transferAmount;
                                filestream1.open("myGCST-ATM-ACCOUNTS.txt", ios::out | ios::trunc);
                                if(!filestream1.fail()){
                                    for(int acc = 0; acc < accountRegistered; acc++){
                                            filestream1 << accounts[acc].username << " " 
                                                        << accounts[acc].accountNumber << " " 
                                                        <<  accounts[acc].email << " " 
                                                        << accounts[acc].pin << " " 
                                                        << accounts[acc].balance << "\n";
                                    }
                                }
                                filestream1.close();
                                long long transRef = generateReferenceNumber();
                                filestream2.open("myGCST-ATM-Transaction" + to_string(accounts[loggedOnAccIndex].accountNumber) + ".txt", ios::out | ios::app);
                                filestream2 << accounts[loggedOnAccIndex].accountNumber 
                                            << " transfer to "
                                            << accounts[receiverAccountIndex].accountNumber
                                            << " with amount of "
                                            << transferAmount << " Ref : "
                                            <<  transRef
                                            << endl;
                                filestream2.close();
                                filestream2.open("myGCST-ATM-Transaction" + to_string(accounts[receiverAccountIndex].accountNumber) + ".txt", ios::out | ios::app);
                                filestream2 << accounts[loggedOnAccIndex].accountNumber 
                                            << " transfer to "
                                            << accounts[receiverAccountIndex].accountNumber
                                            << " with amount of "
                                            << transferAmount << " Ref : "
                                            <<  transRef
                                            << endl;
                                filestream2.close();                            
                                thread td6{[](){
                                    this_thread::sleep_for(delay);
                                    customHeaderMessageWithLine(" Transfer Successful ", maxWidth);
                                }};
                                system("pause");
                                isTransferSuccessful = true;
                                td6.join();
                                system("cls");
                            }else{
                                customHeaderMessageWithLine(" Invalid PIN Number ", maxWidth);
                            }
                        }else{
                            customHeaderMessageWithLine(" Insufficient Balance " , maxWidth);
                        }
                    }else{
                        customHeaderMessageWithLine(" Transfer Amount must be higher than 0 " , maxWidth);
                    }
                }else{
                    customHeaderMessageWithLine(" Invalid Receiver Account Number ", maxWidth);
                }
            }
        }else{
            customHeaderMessageWithLine(" Transfer Amount must be higher than 0 " , maxWidth);
        }
    }
}

void transHistory(){
    string stringInLine;
    fstream filestreamer;
    int page = 1;
    char option;
    system("cls");
    while(page){
        customHeaderMessageWithLine(" Transaction History " , maxWidth);
        filestreamer.open("myGCST-ATM-Transaction" + to_string(accounts[loggedOnAccIndex].accountNumber) + ".txt", ios::in);
        // file to vector
        transactionHistory.clear();
        if(!filestreamer.fail()){
            while(!filestreamer.eof()){
                    getline(filestreamer, stringInLine);
                        if (!stringInLine.empty()) {
                        transactionHistory.push_back(stringInLine);
                    }
                }
            filestreamer.close();
        }else{
            cout << "No trasaction" << endl;
            system("pause");
            break;
        }
        int transactionSize = transactionHistory.size();
        for(int count = (page*10)-10; count < page*10 && count < transactionSize; count++){
            cout << "(" << count + 1 << ") \t" << transactionHistory[count] << endl;
        }
        cout << endl << "Choose Option Below :  " << endl;
        //cout << "(a) Find Transaction using Reference " << endl;
        if(transactionSize > page*10){
            cout << "(b) Next " << endl; 
            cout << "(c) Back " << endl;
            cout << "Option : ";
            cin >> option;
            char optionUpper = toupper(option);
            if(optionUpper == 'A'){
                //findtransacationUsingREF()
                page--;
            }else if(optionUpper == 'B'){
                page++;
            }else if(optionUpper == 'C'){
                page--;
            }else{

            }
        }else{
            cout << "(b) Back " << endl;
            cout << "Option : ";
            cin >> option;
            char optionUpper = toupper(option);
            if(optionUpper == 'A'){
                //findtransacationUsingREF()
                page--;
            }else if(optionUpper == 'B'){
                page--;
            }else{

            }
        }
    }
}

void logOut(){
    int logOutOrNot = 0;
    bool LogOutCancel = false;
    while(!LogOutCancel && !isloggedOut){
        customHeaderMessageWithLine(" Log Out Account " , maxWidth);
        cout << "Are you sure to log out your account ?  " << endl; 
        cout << "Enter 1 if yes and 2 if not : "; 
        logOutOrNot = getIntegerInput();
        if(logOutOrNot == 1){
            loggedOnAccIndex = -1;
            isloggedOut = true;
            system("cls");
        }else if(logOutOrNot == 2){
            LogOutCancel = true;
            customHeaderMessageWithLine(" Log Out Canceled ", maxWidth);
        }else{
            customHeaderMessageWithLine(" Invalid Option ", maxWidth);
        }
    }
}

long long int generateReferenceNumber(){
    long long int res = 0;
    while(res <= 0 ){
        random_device rd;
        mt19937 gen(rd()); 
        long long int min  = 100000000000; 
        long long int max  = 999999999999;   
        uniform_int_distribution<int> distribution(min, max); 
        res = distribution(gen); 
    }
    return res;
}
long long int getInputWithDataValidatorForInt(istream &input, const string inputErrorMessage) {
    long long int res;
    input >> res;
    if (input.fail()) {
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
        customHeaderMessageWithLine(inputErrorMessage, maxWidth);
        res = -1;
    }
    return res;
}
long long getIntegerInput(){
    string input;
    cin >> input;
    if(input[0] == '<' && input.size() == 1){
        return -1;
    }
    if(input.size() > 0){
        for(int c = 0; c < input.size(); c++){
            for(int l = 0; l <= 127; l++){
                char ch = l;
                if(!((l > 48 && l < 57) || l == 57 || l == 48)){
                    if(input[c] == ch){
                        return -2;
                    }
                }
            }
        }
        long long processInput = stoll(input);
        return processInput;
    }
}