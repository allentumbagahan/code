#include <iostream>
using namespace std;

const float pi = 3.14159;
int area(int side1){
    //area of square = side ^ 2
    int res = side1 * side1;
    return res;
}
int area(int length, int width){
    int res = length * width;
    return res;
}
double area(double radius){
    //area of circle = pi * r^2
    double res = pi * (radius * radius);
    return res;
}

int main(){
    cout << "Area of square: " << area(5) << endl;
    cout << "Area of rectangle: " << area(4, 6) << endl;
    cout << "Area of circle: " << area(2.50) << endl;
}