#include <iostream>
using namespace std;

const float pi = 3.14159;
double area(double base, double height){
    return  (base * height) / 2;
}
int area(int base, int height){
    int res = base * height;
    return res;
}
int area(int length, int width, int height){
    return length * width * height;
}

int main(){
    cout << "Area of the triangle: " << area(4.00, 3.75) << endl;
    cout << "Area of the parallelogram: " << area(3, 4) << endl;
    cout << "Volume of the rectangular prism: " << area(4, 2, 3) << endl;
}