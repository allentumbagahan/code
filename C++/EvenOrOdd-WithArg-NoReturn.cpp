#include <iostream>
using namespace std;

void EvenOrOdd(int num1){

	if (num1 % 2 == 0){
		cout << "EVEN NUMBER";
	}
	else {
		cout << "ODD NUMBER";
	}
}

int main(){
	int fnumber;
	cout << "Enter Any Whole Number : ";
	cin >> fnumber;
	EvenOrOdd(fnumber);
}

