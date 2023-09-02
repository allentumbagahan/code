#include <iostream>
#include <string>
using namespace std;

void checkUpper(char char1){
	if ('A' < char1 && char1 < 'Z' ){
		cout<< char1 << " is an uppercase character"<< endl;
	}else{
		cout<< char1 << " is not an uppercase character "<< endl;
	}
}
void checkLower(char char1){
	if ('a' < char1 && char1 < 'z' ){
		cout<< char1 << " is a lowercase character"<< endl;
	}else{
		cout<< char1 << " is not a lowercase character "<< endl;
	}
}

int main()
{
	char char1;
	cout << "Enter a character ";
	cin >> char1;
	checkUpper(char1);
	checkLower(char1);
	return 0;
}