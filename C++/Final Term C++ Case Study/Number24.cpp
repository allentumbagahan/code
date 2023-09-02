#include <iostream>
using namespace std;
int avg(int p1, int p2, int p3, int p4){
    return (p1 + p2 + p3 + p4)/4;
}
double avg(double p1, double p2, double p3, double p4){
    return (p1 + p2 + p3 + p4)/4;
}

int main(){
    int i1, i2, i3, i4;
    float f1, f2, f3, f4;
    cout << "Enter four integers: " << endl;
    cin >> i1;
    cin >> i2;
    cin >> i3;
    cin >> i4;
    cout << "Average of integers: " << avg(i1, i2, i3, i4) << endl;
    cout << "Enter four floats: " << endl;
    cin >> f1;
    cin >> f2;
    cin >> f3;
    cin >> f4;
    cout << "Average of floats: " << avg(f1, f2, f3, f4) << endl;
}