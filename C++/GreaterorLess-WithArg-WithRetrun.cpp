#include <iostream>
#include <string>
using namespace std;

string GreaterOrLess(double, double);

int main(){
	double firstNumber, secondNumber;
	string result;
    cout << "Enter Two Numbers and Determine Greater Number" << endl;
	cout << "Enter First Number : ";
	cin >> firstNumber;
	cout << "Enter Second Number : ";
	cin >> secondNumber;
    result = GreaterOrLess(firstNumber, secondNumber);
	cout << result;
}

string GreaterOrLess(double n1, double n2){
	if (n1 > n2){
		return "First Number is greater than Second Number";
	}
	else {
		return "Second Number is greater than First Number";
	}
}
