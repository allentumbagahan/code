#include<iostream>
#include<string>
using namespace std;

    int choice, func;
    string account, password;
    string accountC, passwordC;
    
    double total_bill=0, bill[100];
    double price[10]={50.00, 15.00, 9.00, 85.00, 8.00, 12.50, 15.00, 25.00, 9.99, 30.00};
    string item[10]={"Milk", "Bread", "Egg", "Chocolate", "Tide", "Rice", "Colgate", "Coffee", "Shampoo", "Rc" };
    int t, quantity;
    int Arr[100];
    string rr[100];
    double amount;
    int del;
    string Del;
    int cartSize = 0;
  
    int main() { 
    
    cout << "--------------------------------------" << endl;
    cout << "Welcome to the GCST Grocery Store!" << endl;
    /*    
    for (int a=1; a<3; a++) {
    cout << "Please select what you want to do: " << endl;
    cout << "1. log-in" << endl;
    cout << "2. Create an account" << endl;
    cout << "3. Exit" << endl << endl;
    
    cout << "Please select an option (1-3): ";
    cin >> choice;
    
    switch (choice) {
    case 1:
    cout << "Please log in to continue" << endl;
    cout << "Enter your name: ";
    cin >> account;
    cout << "Enter your password: ";
    cin >> password;
    
    if (account == accountC && password == passwordC) {
    cout << "Logged in successfully!" << endl;
    } 
    else if (account == accountC && password != passwordC){
    for (t=1; t<=4; t++) {
    if (password == passwordC){
    break;
    }
    cout << "Wrong password!" << endl;
    cout << "Enter your password: ";
    cin >> password;
    }
    if (t==5 && password != passwordC) {
    cout << "For your safety" << endl;
    cout << "Your account has been block for 24hrs"; 
    return 0;
    }
    } else {
    cout << "No account found! " << endl;
    return 0;
    }
    
    break;
    case 2:
    cout << "Please enter a username and password to create a account" << endl;
    cout << "Enter your  Name: ";
    cin >> accountC;
    cout << "Enter your Password: ";
    cin >> passwordC;
    cout << "Account created successfully!" << endl << endl;
    break;
    case 3:
    return 0;
    break;     
    } 
    }

    cout << endl << "Welcome, " << account << "!" << endl;
    */
    do {
    for (int z=0; z>=0; z++) {
    cout << "--------------------------------------" << endl;
    cout << "Item Menu: " << endl;
    cout << "1. Milk - $50.00 " << endl;
    cout << "2. Bread - $15.00 " << endl;
    cout << "3. Egg - $9.00 " << endl;
    cout << "4. Chocolate - $85.00 " << endl;
    cout << "5. Tide - $8.00 " << endl;
    cout << "6. Rice - $12.50 " << endl;
    cout << "7. Colgate - $15.00 " << endl;
    cout << "8. Coffee - $25.00 " << endl;
    cout << "9. Shampoo - $9.99 " << endl;
    cout << "10. RC - $30.00 " << endl;
    cout << "11. Check Out " << endl;
    cout << "12. View Cart " << endl;
    cout << "13. Remove item " << endl;
    cout << "14. Log out " << endl << endl;
     
    cout << "Enter your choice: ";
    cin >> func;
    cout << endl;
    switch (func) {
    case 1:
    cout << "Enter quantity: ";
    cin >> quantity;
    bill[z]=price[0]*quantity;
    cout << "Added " << quantity << " " << item[0] << " to cart.";
    total_bill+=bill[z];
    rr[cartSize]="Milk x ";
    Arr[cartSize]= quantity;
    cartSize++;
    break;
    case 2:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Bread x ";
    Arr[cartSize]= quantity;
    bill[z]=price[1]*quantity;
    cout << "Added " << quantity << " " << item[1] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 3:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Egg x ";
    Arr[cartSize]= quantity;
    bill[z]=price[2]*quantity;
    cout << "Added " << quantity << " " << item[2] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 4:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Chocolate x ";
    Arr[cartSize]= quantity;
    bill[z]=price[3]*quantity;
    cout << "Added " << quantity << " " << item[3] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 5:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Tide x ";
    Arr[cartSize]= quantity;
    bill[z]=price[4]*quantity;
    cout << "Added " << quantity << " " << item[4] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 6:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Rice x ";
    Arr[cartSize]= quantity;
    bill[z]=price[5]*quantity;
    cout << "Added " << quantity << " " << item[5] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 7:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Colgate x ";
    Arr[cartSize]= quantity;
    bill[z]=price[6]*quantity;
    cout << "Added " << quantity << " " << item[6] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 8:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Coffee x ";
    Arr[cartSize]= quantity;
    bill[z]=price[7]*quantity;
    cout << "Added " << quantity << " " << item[7] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 9:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Shampoo x ";
    Arr[cartSize]= quantity;
    bill[z]=price[8]*quantity;
    cout << "Added " << quantity << " " << item[8] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 10:
    cout << "Enter quantity: ";
    cin >> quantity;
    rr[cartSize]="Rc x ";
    Arr[cartSize]= quantity;
    bill[z]=price[9]*quantity;
    cout << "Added " << quantity << " " << item[9] << " to cart.";
    total_bill+=bill[z];
    cartSize++;
    break;
    case 11:
    cout << "Cart summary: " << endl;
    for (int b=0; b<cartSize; b++) {
    cout << rr[b] << Arr[b] << " = " << bill[b] << endl;
    }
    
    cout << "--------------------------------------" << endl;
    cout << "Total Bill: " << total_bill << endl;
    
    do {
    cout << "Enter the amount you have: ";
    cin >> amount;
    
    if (amount < total_bill) {
    cout << "Sorry that's not enough to cover your total bill. Please enter a higher amount." << endl;
    }
    
    }
    while (amount < total_bill);
    
    cout << "Payment: $" << amount << endl;
    cout << "Change: $" << amount-total_bill << endl;
    cout << "Thank you for shopping with us!" <<endl;
    return 0;
    break;
    case 12:
    cout << "Cart summary: ";
    for (int b=0; b<cartSize; b++) {
    cout << rr[b] << Arr[b] << " = " << bill[b] << endl;
    }
    
    cout << "--------------------------------------" << endl;
    cout << "Total Bill: " << total_bill << endl;
    
    break;
    case 13:
    cout << "Please select an item to remove (1-10): ";
    cin >> del;
    cout << "Remove " << item[del-1] << " from cart." << endl;
    // find the item
    for(int i = 0; i < cartSize; i++){
        cout << rr[i] << endl;
        cout << item[del - 1] + " x " << endl;
        if(rr[i] == item[del - 1] + " x "){
            total_bill -= bill[del - 1];
            cartSize--;
            // adjust the array value 
            for(int r = i; r < cartSize + 1; r++){
                rr[r] = rr[ r + 1];
                Arr[r] = Arr[ r + 1];
            }
            break;
        }
    }
    
    break;
    case 14:
    return 0;
    break;
    default:
    cout << "Check your input!" << endl;
    return 0;
    break;     
    }
    
    if (func == 11 || func == 12 || func == 13){
    z-=1;
    }
    
    cout << endl;
    } 
    
    }
    
    while (func != 14);
    
    return 0;
}