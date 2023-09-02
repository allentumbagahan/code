#include <iostream>
#include <string>
using namespace std;
string isEmpty(const string& str) {
    bool check = str.empty();
    if (check) {
        return "Yes";
    } else {
        return "No";
    }
}
string isEmpty(char ch) {
    bool check = (ch == '\0');
    if (check) {
        return "Yes";
    } else {
        return "No";
    }
}
int main(){
    string s1;
    char s2;
    cout << "Enter a string : ";
    cin >> s1;
    cout << "Is the string empty? " << isEmpty(s1) << endl;
    cout << "Enter a character : ";
    cin >> s2;
    cout << "Is the character empty? " << isEmpty(s2) << endl;
}
