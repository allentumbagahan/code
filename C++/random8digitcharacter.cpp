#include <iostream>
#include <random>
#include <string>
using namespace std;
int main() {
    string randomString;
    const string validCharacters = "0123456789abcdef";

    // Random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, validCharacters.size() - 1);

    // Generate 8-digit random string
    for (int i = 0; i < 8; ++i) {
        randomString += validCharacters[dis(gen)];
    }

    cout << "Random String: " << randomString << endl;

    return 0;
}