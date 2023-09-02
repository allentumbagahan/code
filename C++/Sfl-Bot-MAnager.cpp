#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
int main() {
    std::string input1 = "1";
    std::string input2 = "1";

    // Execute the sflBot.exe file with input redirection
    std::string command = "C:\\Users\\allen\\OneDrive\\code\\C++\\sflBot.exe";
    system(command.c_str());
    command = "echo " + input1 + " & echo " + input2 ;
    this_thread::sleep_for(4s);
    system(command.c_str());
    return 0;
}