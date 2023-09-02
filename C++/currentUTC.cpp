#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;
int main() {
    // Get the current UTC time
    auto currentTime = chrono::system_clock::now();
    auto utcTime = chrono::time_point_cast<chrono::milliseconds>(currentTime);

    // Convert the UTC time to a string in the desired format
    time_t time = chrono::system_clock::to_time_t(utcTime);
    tm* gmTime = gmtime(&time);

    // Format the string
    stringstream ss;
    ss << setfill('0') << setw(4) << gmTime->tm_year + 1900 << "-" << setw(2) << gmTime->tm_mon + 1 << "-" << setw(2) << gmTime->tm_mday << "T" << setw(2) << gmTime->tm_hour << ":" << setw(2) << gmTime->tm_min << ":" << setw(2) << gmTime->tm_sec << "." << setw(3) << utcTime.time_since_epoch().count() % 1000 << "Z";
    string formattedTime = ss.str();

    // Print the formatted UTC time
    cout << formattedTime << endl;

    return 0;
}