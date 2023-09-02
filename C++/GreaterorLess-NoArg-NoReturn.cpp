#include <iostream>
using namespace std;

void GreaterOrLess();

int main(){
    cout << "Enter Two Numbers and Determine Greater Number" << endl;
    GreaterOrLess();
}

void GreaterOrLess(){
    double firstNumber, secondNumber;
	cout << "Enter First Number : ";
	cin >> firstNumber;
	cout << "Enter Second Number : ";
	cin >> secondNumber;
	if (firstNumber > secondNumber){
		cout << "First Number is greater than Second Number";
	}
	else {
		cout << "Second Number is greater than First Number";
	}
	
}
