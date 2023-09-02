#include <iostream>

using namespace std;

bool isPositive(int n) {
    return n > 0;
}

bool isPositive(float n) {
    return n > 0.0;
}

int main() {
    int integerNumber;
    float floatNumber;
    cout << "Enter an integer: ";
    cin >> integerNumber;
    cout << integerNumber << " is " << ((isPositive(integerNumber))? "positive" : "not positive") << endl;
    cout << "Enter a float number: ";
    cin >> floatNumber;
    cout << floatNumber << " is " << ((isPositive(floatNumber))? "positive" : "not positive") << endl;
}
