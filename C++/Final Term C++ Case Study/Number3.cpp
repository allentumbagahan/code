#include <iostream>
using namespace std;

int sqrt(int p1){
    int res = p1 * p1;
    return res;
}
double sqrt(double p1){
    double res = p1 * p1;
    return res; 
}

int main(){
    cout << "Square of 5 (integer): ";
    cout << sqrt(5) << endl;
    cout << "Square of 2.5 (double): ";
    cout << sqrt(2.5) << endl;
}