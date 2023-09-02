#include <iostream>
using namespace std;

int findMin(int int1, int int2){
    if(int1 < int2){
        return int1;
    }else {
        return int2;
    }
}
float findMin(float d1, float d2){
    if(d1 < d2){
        return d1;
    }else {
        return d2;
    }
}
int main(){
    int i1, i2;
    float f1, f2;
    cout << "Enter two integers: " << endl;
    cin >> i1;
    cin >> i2;
    cout << "Minimum value among the integers: " << findMin(i1, i2) << endl;
    cout << "Enter two float numbers: " << endl;
    cin >> f1;
    cin >> f2;
    cout << "Minimum value among the float numbers: " << findMin(f1, f2) << endl;
}