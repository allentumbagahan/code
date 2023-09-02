#include <iostream>
using namespace std;

const float pi = 3.14159;
void calculate(int length, int width){ 
    cout << length * width << endl;
}
void calculate(int length, int width, int height){
    cout << length * width * height << endl;
}
void calculate(double radius, int height){
    //Volume of cylinder formula = pi * r^2 * height
    cout << (pi * (radius * radius)) * height << endl;
}

int main(){
    cout << "Area of rectangle: ";
    calculate(2.0, 7.5) ;
    cout << "Volume of rectangle prism: ";
    calculate(3.0, 5.0, 3.0);
    cout << "Volume of cylinder: " ;
    calculate(1.2906677, 15);
}