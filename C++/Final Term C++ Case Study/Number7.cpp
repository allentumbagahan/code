#include <iostream>
using namespace std;

int calculateArea(int side1){
    //area of square = side ^ 2
    return side1 * side1;
}
int calculateVol(int side){
    //volume cube = side ^ 3
    return side * side * side;
}

int main(){
    cout << "Area of square: " << calculateArea(5) << endl;
    cout << "Volume of cube: " << calculateVol(5) << endl;
}