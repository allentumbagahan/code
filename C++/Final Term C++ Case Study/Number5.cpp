#include <iostream>
using namespace std;

int findMax(int int1, int int2){
    if(int1 > int2){
        return int1;
    }else {
        return int2;
    }
}
double findMax(double d1, double d2){
    if(d1 > d2){
        return d1;
    }else {
        return d2;
    }
}
int main(){
    cout << "Maximum of 10 and 15: " << findMax(10, 15) << endl;
    cout << "Maximum of 3.5 and 2.8: " << findMax(3.5, 2.8) << endl;
}