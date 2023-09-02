#include <iomanip>
#include <vector>
#include <functional>
#include <sstream>
#include <iostream>
#include <limits>
#include <fstream>
#include <ctime>

using namespace std;

void processSelection(int, const vector<function<void()>>);
void customHeaderMessageWithLine(string, int, char = '*', bool = false);
int getSelectionInputWithDataValidator(istream&, int, string, string);
long long int getInputWithDataValidatorForInt(istream&, string);
void createRecord();
void showAll();
bool validatebirthday(string);
int getAge(string);
void update();
void loadData();
void findData();
void deleteData();

struct student{
    int studentID;
    string fullname;
    string birthdate;
    string course;
    int yearLevel;
    char section;
    int age;
    long long int contactNumber;

};
vector<student> students;
int maxWidth = 90;
bool updateOnly = false;
string studentNumTemp; // for modification(update)
int main(){
    vector<function<void()>> selections1 = {createRecord, showAll, findData, update, deleteData};
    while(1){
        int selected;
        customHeaderMessageWithLine("\033[34m Welcome To GCST Student Management System \033[0m", maxWidth);
        cout << endl << "\033[32m" << ">>  Choose Any Option Below : " << "\033[0m"
             << endl << "1.) Create New Student Record "
             << endl << "2.) Show All Student Records "
             << endl << "3.) Find Student Record "
             << endl << "4.) Update Student Records "
             << endl << "5.) Delete Student Records "
             << endl << "Choose Option :  ";
        selected = getSelectionInputWithDataValidator(cin, 5, " Invalid Option ", " Out of Option Range ");
        processSelection(selected, selections1);
    }
}

void createRecord(){
    bool isCreated;
    string tempSection;
    char tempSectionChar;
    int updateItemIndex;
    if(updateOnly){
        if(studentNumTemp.size() == 7){
            if((stoi(studentNumTemp.substr(2, studentNumTemp.size()))) <= students.size()){
                updateItemIndex = (stoi(studentNumTemp.substr(2, studentNumTemp.size()))) - 1;
                cout << "Found Student " << endl;
            }else{
                isCreated = true;
                updateOnly = false;            
            }
        }else{
            isCreated = true;
            updateOnly = false;    
        }
        system("pause");
    }
    while(!(isCreated)){
        student newStudent;
        customHeaderMessageWithLine((!updateOnly)? " Create New Student Record " : " Update Student Record ", maxWidth);
        cout << "Enter FullName : ";
        cin.ignore();
        getline(cin, newStudent.fullname);
        cout << "Enter Contact # (63)";
        newStudent.contactNumber = getInputWithDataValidatorForInt(cin, " Invalid Contact Number ");
        if(!(newStudent.contactNumber == -1)){
            if(newStudent.contactNumber < 9999999999 && newStudent.contactNumber > 9000000000){
            cin.ignore();
            cout << "Enter Birthdate (mm/dd/yyyy) : ";
            getline(cin, newStudent.birthdate);
                if(validatebirthday(newStudent.birthdate)){
                    cout << "Enter Academic Level (1-4) : ";
                    newStudent.yearLevel = getInputWithDataValidatorForInt(cin, " Invalid Year Level ");
                    if(!(newStudent.yearLevel == -1)){
                        if(newStudent.yearLevel < 5){
                            cin.ignore();
                            cout << "Enter Course (UPPERCASE): ";
                            getline(cin, newStudent.course);
                            cout << "Enter Section (A-F) : ";
                            getline(cin, tempSection);
                            if(tempSection.size() == 1 ){
                                tempSectionChar = toupper(tempSection[0]);
                                if((tempSectionChar > 'A' || tempSectionChar == 'A') && tempSectionChar < 'G'){
                                    newStudent.section = tempSectionChar;
                                    newStudent.age = getAge(newStudent.birthdate);
                                        fstream fileStreamer;
                                        if(!updateOnly){
                                            fileStreamer.open("myStudentInformations.txt", ios::out | ios::app);
                                            if(!fileStreamer.fail()){
                                                fileStreamer << newStudent.fullname << ","
                                                             << newStudent.birthdate << ","
                                                             << newStudent.course << ","
                                                             << newStudent.yearLevel << ","
                                                             << newStudent.section << ","
                                                             << newStudent.age << ","
                                                             << newStudent.contactNumber << endl;
                                            }
                                            fileStreamer.close();
                                            isCreated = true;
                                        }else{
                                            int studentsSize = students.size();
                                            fileStreamer.open("myStudentInformations.txt", ios::out | ios::trunc);
                                            fileStreamer.close();
                                            fileStreamer.open("myStudentInformations.txt", ios::out | ios::app);
                                            if(!fileStreamer.fail()){
                                                for(int l = 0; l < studentsSize; l++){
                                                    if(l == updateItemIndex){
                                                        fileStreamer << newStudent.fullname << ","
                                                             << newStudent.birthdate << ","
                                                             << newStudent.course << ","
                                                             << newStudent.yearLevel << ","
                                                             << newStudent.section << ","
                                                             << newStudent.age << ","
                                                             << newStudent.contactNumber << endl;
                                                             continue;
                                                    }
                                                    fileStreamer << students[l].fullname << ", "
                                                             << students[l].birthdate << ", "
                                                             << students[l].course << ","
                                                             << students[l].yearLevel << ","
                                                             << students[l].section << ","
                                                             << students[l].age << ","
                                                             << students[l].contactNumber << endl;
                                                }
                                            }
                                            fileStreamer.close();
                                            isCreated = true;
                                            updateOnly = false;                                                                                       
                                        }
                                }else{
                                    customHeaderMessageWithLine(" Invalid Section ", maxWidth);
                                }
                            }else{
                                customHeaderMessageWithLine(" Invalid Section ", maxWidth);
                            }
                        }else{
                        customHeaderMessageWithLine(" Year Level cannot exceed to 4 ", maxWidth);
                        }
                    }
                }
            }else{
            customHeaderMessageWithLine(" Invalid Contact Number ", maxWidth);
            }
        }
    }
    system("cls");
}

void showAll(){
    int highSize = 0, highSize2 = 0, highSize3 = 0;
    students.clear();
    loadData();
    int studentSize =  students.size();
    if(studentSize > 0){
        for(int s = 0; s < studentSize; s++){
            if(((students[s].fullname).size()) > highSize){
                highSize = (students[s].fullname).size();
            }
            if(((students[s].course).size()) > highSize2){
                highSize2 = (students[s].course).size();
            }
        }
        system("cls");
        customHeaderMessageWithLine(" All Student Records ", maxWidth);
        int spacing1 = ((highSize > 12)? (highSize - 12) : (12 - highSize));
        cout << "Student Name" << setfill(' ') << setw(13) << "" 
             << "Course" << setfill(' ') << setw(highSize2) << "" 
             << "Section" << setfill(' ') << setw(4) << ""
             << "Year Level" << setfill(' ') << setw(4) << ""
             << "Contact#" << setfill(' ') << setw(5) << ""
             << "Age" << setfill(' ') << setw(2) << ""
             << "Student Num." << endl;
        for(int studentIndex = 0; studentIndex < studentSize; studentIndex++){
            int spacing;
            string tempId = "AB00000" + to_string(studentIndex + 1);
            while(tempId.size() > 7){
                tempId = tempId.substr(3, 7);
            }
            if((students[studentIndex].fullname).size() <= 25){
                spacing = 25 - (students[studentIndex].fullname).size();
            }else{
                string cropName = (students[studentIndex].fullname).substr(0, 25);
                spacing = 25 - cropName.size();
            }
            cout << students[studentIndex].fullname << setfill(' ') << setw(spacing + 1) << "";
            cout << students[studentIndex].course << setfill(' ') << setw(8 + (highSize2 - (students[studentIndex].course).size())) <<"";
            cout << students[studentIndex].section  << setfill(' ') << setw(11) <<"";
            cout << students[studentIndex].yearLevel << setfill(' ') << setw(7) <<"";
            cout << "63" << students[studentIndex].contactNumber << setfill(' ') << setw(3) <<"";
            cout << students[studentIndex].age << setfill(' ') << setw(5) <<"";
            cout << "AB" + tempId << endl;
            students[studentIndex].studentID = stoi(tempId);
        }
    }else{
        customHeaderMessageWithLine(" All Student Records ", maxWidth);
        customHeaderMessageWithLine(" No Student Records ", maxWidth, ' ', true);
    }
    customHeaderMessageWithLine("**", maxWidth);
    system("pause");
    
}

void processSelection(int s, const vector<function<void()>> func) {
    int maxSize = func.size();
    if(s - 1 < maxSize && s > 0){
        func[s - 1]();
    } 
}

void customHeaderMessageWithLine(string msg, int maxWidth, char s, bool red){
    if(red){   
        msg = "\033[31m" + msg + "\033[0m";
    }
    int halflinecount = (maxWidth - msg.size())/2;
    cout  << endl << setfill(s) << setw(halflinecount + 1) << " ";
    cout  << msg;
    if(((maxWidth - msg.size()) % 2 == 1) ){
        cout  << " "<< setfill(s) << setw(halflinecount + 1) << "" << endl << endl;
    }else{
        cout  << " "<< setfill(s) << setw(halflinecount) << "" << endl << endl;
    }
}

int getSelectionInputWithDataValidator(istream &input, int sizeOfSelection, string inputErrorMessage, string overLimitMessage){
    int select;
    input >> select;
    if(input.fail()){
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
        select = -1; // if fail set the selection into -1
        customHeaderMessageWithLine(inputErrorMessage, maxWidth, true);
    }else{
        if(!(select > 0 && select < sizeOfSelection + 1)){
            select = -1; // if doesnt meet the req. then selection set to -1
            customHeaderMessageWithLine(overLimitMessage, maxWidth, true);
        }
    }
    return select;
}

long long int getInputWithDataValidatorForInt(istream &input, const string inputErrorMessage) {
    long long int res;
    input >> res;
    if (input.fail()) {
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
        customHeaderMessageWithLine(inputErrorMessage, maxWidth);
        res = -1;
    }
    return res;
}
bool validatebirthday(string bday){
    bool res = false;
    string year;
    if(bday.size() < 9){
        customHeaderMessageWithLine("Invalid Birthdate Format", maxWidth);
        return false;
    }
    if(bday[2] == '/' && bday[5] == '/' && (bday.size() < 10 || bday.size() == 10)){
       if(bday[0] == '0'){
            if((bday[1] < '9' || bday[1] == '9') && bday[1] > '0'){
                res = true;
            }else{
                customHeaderMessageWithLine("Invalid Birth-Month Format", maxWidth);
                return false;
            }
       }else if(bday[0] == '1'){
            if(bday[1] < '3' && (bday[1] > '0' || bday[1] == '0')){
                res = true;
            }else{
                customHeaderMessageWithLine("Birth-Month cannot exceed to 12", maxWidth);
                return false;
            }
       }else{
            customHeaderMessageWithLine("Birth-Month cannot exceed to 12", maxWidth);
            return false;
       }
    }else{
        customHeaderMessageWithLine("Invalid Birthdate Format", maxWidth);
        return false;
    }
    if(bday[3] > '3'){
        customHeaderMessageWithLine("Invalid Birth-Day Format", maxWidth);
        res = false;
    }else{
        if(bday[3] == '3'){
            if(bday[4] > '1'){
                customHeaderMessageWithLine("Birth-Month cannot exceed to 31", maxWidth);
                return false;
            }
        }else if(bday[3] == '2' && (bday[4] > '0' || bday[4] == '0') && (bday[4] < '9' || bday[4] == '9')){
            res = true;
        }else if(bday[3] == '1' && (bday[4] > '0' || bday[4] == '0') && (bday[4] < '9' || bday[4] == '9')){
            res = true;
        }else if(bday[3] == '0' && (bday[4] > '0' || bday[4] == '0') && (bday[4] < '9' || bday[4] == '9')){
            res = true;
        }else{
            customHeaderMessageWithLine("Invalid Birth-Day Format", maxWidth);
            return false;
        }
    }
    for(int c = 6; c < bday.size(); c++){
        year += bday[c];
    }
    if(stoi(year) >= 2023){
        customHeaderMessageWithLine("Invalid Birth-Year", maxWidth);
        return false;
    }
    return res;
}
int getAge(string birthdateStr) {
  time_t currentTime = time(nullptr);
  tm birthdate = {};
  istringstream ss(birthdateStr);
  ss >> get_time(&birthdate, "%m/%d/%Y");
  time_t birthTime = mktime(&birthdate);
  time_t difference = currentTime - birthTime;
  tm age = *gmtime(&difference);
  int years = age.tm_year - 70;
  return years;
}

void update(){
    loadData();
    cout << "Enter Student Number : ";
    cin >> studentNumTemp;
    updateOnly = true;
    createRecord();
}
void loadData(){
    students.clear();
    fstream filestream1;
    string stringInLine, propertyInString, ylevel, section, gContactNumber, age, contactNumber; 
    filestream1.open("myStudentInformations.txt");
    if(!filestream1.fail()){
        while(!filestream1.eof()){
            getline(filestream1, stringInLine);
            if (!stringInLine.empty()) {
                    student acc;  
                    stringstream ss(stringInLine);
                    getline(ss, acc.fullname, ',');
                    getline(ss, acc.birthdate, ',');
                    getline(ss, acc.course, ',');
                    getline(ss, ylevel, ',');
                    acc.yearLevel = stoi(ylevel); //stoi means string to int
                    getline(ss, section, ',');
                    acc.section = section[0];
                    getline(ss, age, ',');
                    acc.age =  stoi(age);
                    getline(ss, contactNumber, ',') ;
                    acc.contactNumber = stoll(contactNumber);
                    students.push_back(acc);  // Add the student to the students(vector)
                }
            }
        filestream1.close();
    }
}

void findData(){
    string findame;
    loadData();
    cout << "Enter Student Full Name : ";
    cin >> findame;
    for(int s = 0; s < students.size(); s++){
        if(students[s].fullname == findame){
            cout << "Found Student" << endl;
            cout << "Course : " << students[s].course << endl;
            cout << "Year Level : " << students[s].yearLevel << endl;
            cout << "Section : " << students[s].section << endl;
            cout << "Age : " << students[s].age << endl;
            cout << "Contact # : " << students[s].contactNumber << endl;
            system("pause");
            break;
        }
    }
    system("cls");
}

void deleteData(){
    string studentNumDeleteTemp;
    int option;
    int deleteItemIndex;
    loadData();
    fstream fileStreamer;
    cout << "Enter Student Number : ";
    cin >> studentNumDeleteTemp;
    if(studentNumDeleteTemp.size() == 7){
        if((stoi(studentNumDeleteTemp.substr(2, studentNumDeleteTemp.size()))) <= students.size() && (studentNumDeleteTemp[0] == 'A' || studentNumDeleteTemp[0] == 'a') && (studentNumDeleteTemp[1] == 'B' || studentNumDeleteTemp[1] == 'b')){
            deleteItemIndex = (stoi(studentNumDeleteTemp.substr(2, studentNumDeleteTemp.size()))) - 1;
            cout << "Are you sure remove " << students[deleteItemIndex].fullname << endl;
            cout << "Enter 1 to Confirm " << endl;
            option = getSelectionInputWithDataValidator(cin, 2, " Invalid Option ", " Out of Option Range ");
            students.erase(students.begin() + deleteItemIndex);
            int studentsSize = students.size();
            if(option == 1){
                fileStreamer.open("myStudentInformations.txt", ios::out | ios::trunc);
                fileStreamer.close();
                fileStreamer.open("myStudentInformations.txt", ios::out | ios::app);
                if(!fileStreamer.fail()){
                    for(int l = 0; l < studentsSize; l++){
                        fileStreamer << students[l].fullname << ", "
                                 << students[l].birthdate << ", "
                                 << students[l].course << ","
                                 << students[l].yearLevel << ","
                                 << students[l].section << ","
                                 << students[l].age << ","
                                 << students[l].contactNumber << endl;
                    }
                }
                fileStreamer.close();
            }
        }else{          
        }
    }
}