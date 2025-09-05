#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int sobaka, luka, nekit;
    cin >> nekit >> luka >> sobaka;
    if (abs(sobaka - luka) <= abs(sobaka - nekit)) {
        cout << "Kashtanka" << endl;
    } else {
        cout << "Tetka" << endl;
    }
    return 0;
}