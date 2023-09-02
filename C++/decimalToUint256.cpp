#include <sstream>
#include <string>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <fstream>
using namespace std;
string decimalToUint256(uint64_t decimal);

int main(){
    cout << decimalToUint256(83792);
}
string decimalToUint256(uint64_t decimal) {
    stringstream ss;
    ss << hex << setfill('0') << setw(64) << decimal;
    return ss.str();
}