#include <cmath>
#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    long long mers = pow(2, a) - 1;
    int modd;
    for (int i = 1; i < a; i++) {
        if (i == 1) {
            modd = 4;
        }
        else {
            modd = (modd * modd - 2) % mers;
        }
    }
    if (modd == 0) {
        cout << "Число простое " << mers;
    }
    else {
        cout << "Число не простое " << mers;
    }
    return 0;
}