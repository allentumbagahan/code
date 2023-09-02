#include <iostream>
using namespace std;

const float pi = 3.14159;
int area(int side1){
    int res = 4 * side1;
    return res;
}
int area(int length, int width){
    int res = 2 * (length + width);
    return res;
}
double area(double radius){
    double res = 2 * pi * radius;
    return res;
}

int main(){
    int squareSide;
    int recLength, recWidth;
    double circleRadius;
    cout << "Enter the side length of the square: ";
    cin >> squareSide;
    cout << "Perimeter of square: " << area(squareSide) << endl;
    cout << "Enter the length and width of the rectangle: " << endl;
    cout << "Enter Length : ";
    cin  >> recLength;
    cout << "Enter Width : ";
    cin  >> recWidth;
    cout << "Perimeter of the rectangle: " << area(recLength, recWidth) << endl;
    cout << "Enter the radius of the circle: ";
    cin >> circleRadius;
    cout << "Circumference of the circle: " << area(circleRadius) << endl;
}