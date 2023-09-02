#include <iostream>
using namespace std;

void multiply(float p1, float p2){
    float res = p1 * p2;
    cout << res << endl;
}
void multiply(int p1, int p2){
    int res = p1 * p2;
    cout << res << endl;
}
void multiply(string word, int multiplier){
    string res;
    for(int t = 1; t <= multiplier; t++){
        res += word;
    }
    cout << res << endl;
}

int main(){
    multiply(25, 2);
    multiply(2.0f, 3.75f);
    multiply("Granby ", 3);
}