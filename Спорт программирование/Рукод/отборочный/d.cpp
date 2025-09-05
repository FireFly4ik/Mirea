#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    long x, y, r;
    cin >> x >> y >> r;
    x = abs(x);
    y = abs(y);
    if (x > y) {
        long temp = y;
        y = x;
        x = temp;
    }
    if (x == 0 && y == 0) {
        cout << 5 << endl;
        return 0;
    } else if (x == 0 || y == 0) {
        if (r > x + y) {
            cout << 5 << endl;
            return 0;
        } else {
            cout << 3 << endl;
            return 0;
        }
    } else {
        if (r < x) {
            cout << 1 << endl;
            return 0;
        } else if (r == x) {
            cout << 2 << endl;
            return 0;
        } else if (r <= y) {
            cout << 3 << endl;
            return 0;
        } 
        double diag = sqrt(x * x + y * y);
        if (double(r) <= diag) {
            cout << 4 << endl;
        } else {
            cout << 5 << endl;
        }
    }
    return 0;
}