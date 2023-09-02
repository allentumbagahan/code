#include <iostream>
using namespace std;

int sum(long int p1, long int p2){
    return p1 + p2;
}
int sum(double p1, double p2){
    return p1 + p2;
}

int main(){
    cout << "Sum of two long integers: " << sum(15l, 15l) << endl;
    cout << "Sum of two long integers: " << sum(2.0, 2.0) << endl;
}