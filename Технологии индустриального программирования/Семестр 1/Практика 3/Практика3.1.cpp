#include <iostream>
#include <string>
using namespace std;

int main(){
    int a;
    cin >> a;
    string sec, minutes, hours;
    sec = to_string(a % 60);
    minutes = to_string(a % 3600 / 60);
    hours = to_string(a / 3600);
    if (minutes.length() < 2){
        minutes = "0" + minutes;
    }
    if (sec.length() < 2){
        sec = "0" + sec;
    }
    cout << hours << ":" << minutes << ":" << sec;
    return 0;
}