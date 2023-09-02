#include <iostream>
using namespace std;

int sum(long p1, long p2, long p3){
    return p1 + p2 + p3;
}
int sum(double p1, double p2, double p3){
    return p1 + p2 + p3;
}

int main(){
    long l1, l2, l3;
    double d1, d2, d3;
    cout << "Enter three long integers :" << endl;
    cin >> l1;
    cin >> l2;
    cin >> l3;
    cout << "Sum of long integers : " << sum(l1, l2, l3) << endl;
    cout << "Enter three double :" << endl;
    cin >> d1;
    cin >> d2;
    cin >> d3;
    cout << "Sum of double integers : " << sum(d1, d2, d3) << endl;
}