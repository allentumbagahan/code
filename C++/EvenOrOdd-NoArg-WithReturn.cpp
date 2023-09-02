#include <iostream>
#include <string>
using namespace std;

string EvenOrOdd(){
	int firstNumber;
	
	cout << "Enter Any Whole Number : ";
	cin >> firstNumber;
	
	if (firstNumber % 2 == 0){
		return "EVEN NUMBER";
	}
	else {
		return "ODD NUMBER";
	}
}

int main(){
	string res;
	res = EvenOrOdd();
	cout << res;
}

