#include <iostream>
using namespace std;

double average(int i1, int i2, int i3){
    return (i1 + i2 + i3)/3.0 ;
}
double average(float f1, float f2, float f3){
    return (f1 + f2 + f3)/3;
}

int main(){
    cout << "Average of three integers: " << average(5, 8, 7) << endl;
    cout << "Average of three floats: " << average(2.02f, 4.57, 1.51) << endl;
}