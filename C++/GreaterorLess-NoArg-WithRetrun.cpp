#include <iostream>
#include <string>
using namespace std;

string GreaterOrLess();

int main(){
	string result;
    cout << "Enter Two Numbers and Determine Greater Number" << endl;
    result = GreaterOrLess();
	cout << result;
}

string GreaterOrLess(){
    double firstNumber, secondNumber;
	cout << "Enter First Number : ";
	cin >> firstNumber;
	cout << "Enter Second Number : ";
	cin >> secondNumber;
	if (firstNumber > secondNumber){
		return "First Number is greater than Second Number";
	}
	else {
		return "Second Number is greater than First Number";
	}
	
}
