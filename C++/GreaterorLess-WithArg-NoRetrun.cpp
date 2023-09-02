#include <iostream>
using namespace std;

void GreaterOrLess(double, double);

int main(){
	double firstNumber, secondNumber;
    cout << "Enter Two Numbers and Determine Greater Number" << endl;
	cout << "Enter First Number : ";
	cin >> firstNumber;
	cout << "Enter Second Number : ";
	cin >> secondNumber;
    GreaterOrLess(firstNumber, secondNumber);
}

void GreaterOrLess(double n1, double n2){
	if (n1 > n2){
		cout << "First Number is greater than Second Number";
	}
	else {
		cout << "Second Number is greater than First Number";
	}
}
