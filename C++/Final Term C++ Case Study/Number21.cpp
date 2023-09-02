#include <iostream>
#include <cmath>
using namespace std;

const float pi = 3.14159;
int cal(int base, int height){
    return (base * height) /2;
}
double cal(int radius){
    return (4.0/3.0) * pi *  pow(radius, 3);
}

int main(){
    int base, height, radius;
    cout << "Enter the base and height of the triangle: " << endl;
    cin >> base;
    cin >> height;
    cout << "Area of triangle: " << cal(base, height) << endl;
    cout << "Enter the radius of sphere: " << endl;
    cin >> radius;
    cout << "Volume of sphere: " << cal(radius) << endl;
}