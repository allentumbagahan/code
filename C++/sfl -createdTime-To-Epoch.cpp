#include <iostream>
#include <chrono>
using namespace std;

int main() {
    long long createdTimeInEpoch = 1692932633673;
    auto currentTime = chrono::system_clock::now();
    auto currentEpochTime = chrono::duration_cast<chrono::seconds>(currentTime.time_since_epoch()).count();
    long long timeDifference = currentEpochTime - (createdTimeInEpoch / 1000);
    int minutes = static_cast<int>(timeDifference / 60);
    int seconds = static_cast<int>(timeDifference % 60);
    cout << createdTimeInEpoch << " Time Difference: " << minutes  << " minutes " << seconds << " seconds" << std::endl;
}
