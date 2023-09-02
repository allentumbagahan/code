#include <iostream>
using namespace std;
int main(){
    int num1 = 2;
    char c = num1;
    cout << c << " ca";
    int last = 127;
    for(int l = 0; l < last + 1; l++){
        char c = l;
        cout << c << " : " << l << endl;
    }
}