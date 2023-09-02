#include <iostream>
using namespace std;

void add(int int1, int int2){
    int res = int1 + int2;
    cout << res << endl;
}
void add(int int1, int int2, int int3){
    int res = int1 + int2 + int3;
    cout << res << endl;
}
void add(string s1, string s2){
    string res = s1 + s2;
    cout << res << endl;
}

int main(){
    add(15, 15);
    add(30, 30, 30);
    add("Granby", "Colleges");
}