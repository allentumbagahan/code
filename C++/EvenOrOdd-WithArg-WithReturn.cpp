#include <iostream>
#include <string>
using namespace std;

string EvenOrOdd(int n1){

	if (n1 % 2 == 0){
		return "EVEN NUMBER";
	}
	else {
		return "ODD NUMBER";
	}
}

int main(){
	int fnum;
	cout << "Enter Any Whole Number : ";
	cin >> fnum;
	string res;
	res = EvenOrOdd(fnum);
	cout << res;
}

