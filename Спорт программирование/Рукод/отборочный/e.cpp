#include <iostream>
using namespace std;

long long comb(long long n) {
    return n * (n - 1) / 2;
}

void f(long long n, long long m) {
    long long a = 2;
    while (comb(a) < m) {
        a++;
    }
    if (a > n) {
        cout << -1 << endl;
        return;
    }
    long long b = n - m;
    if (b < 1) {
        cout << 1 << " ";
    } else {
        cout << b << " ";
    }
    cout << n - a + 1 << endl;
}

int main() {
    long long n, m;
    cin >> n >> m;
    f(n, m);
    return 0;
}