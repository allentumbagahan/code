#include <iostream>
using namespace std;

string divisible(int int1){
    if(int1 % 2 == 0){
        return "Yes";
    }else {
        return "No";
    }
}
string divisible(double d1){
    int whole = d1;
    double decimal = d1 - whole;
    if(decimal > 0.0){
        // decimal with a fraction greater with 0.0 is not divisible by 2
        return "No";
    }else {
        if(whole % 2 == 0){
            return "Yes";
        }else{
            return "No";
        }
    }
}
int main(){
    cout << "Maximum of 10? " << divisible(10) << endl;
    cout << "Maximum of 7.5:? " << divisible(7.5) << endl;
}