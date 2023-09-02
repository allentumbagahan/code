#include <iostream>
using namespace std;

string checkVol(char let){
    if(let == 'a' || let == 'e' || let == 'i' || let == 'o' || let == 'u' ){
        return "Yes";
    }else{
        return "No";
    }
}
string checkCon(char let){
    if(let == 'a' || let == 'e' || let == 'i' || let == 'o' || let == 'u' ){
        return "No";
    }else{
        return "Yes";
    }
}

int main(){
    cout << "a is a vowel? " << checkVol('a') << endl;
    cout << "b is a consonat? " << checkCon('b') << endl;
}