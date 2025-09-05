#include <iostream>
#include <vector>
using namespace std;

int main() {
    float a, b;
    cin >> a >> b;
    cout << int(a / b * 10) % 10 << endl;
    return 0;
}