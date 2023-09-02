#include <iostream>
using namespace std;

void EvenOrOdd(){
	int firstNumber;
	
	cout << "Enter Any Whole Number : ";
	cin >> firstNumber;
	
	if (firstNumber % 2 == 0){
		cout << "EVEN NUMBER";
	}
	else {
		cout << "ODD NUMBER";
	}
}

int main(){
	EvenOrOdd();
}

