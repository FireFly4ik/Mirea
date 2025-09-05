#include <iostream>
#include <vector>
#include <string>
using namespace std;

void flush() {
    cout.flush();
}

int ask(long long t) {
    cout << "? " << t << endl;
    flush();
    int d;
    cin >> d;
    return d;
}

void answer(unsigned int n) {
    cout << "! " << n << endl;
    flush();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> bits(32, 0);
    unsigned int n = 0;

    for (int k = 0; k < 32; k++) {
        long long t = 1LL << k;
        int d = ask(t);
        if (d == 1) {
            bits[k] = 0;
        } else {
            for (int i = 0; i > d; i--) {
                if (k == 32) {
                    break;
                }
                bits[k] = 1;
                k++;
            }
            bits[k] = 0;
        }
    }

    unsigned long long result = 0;
    for (int i = 0; i < 32; i++) {
        if (bits[i] == 1) {
            result |= (1ULL << i);
        }
    }
    answer(result);
    return 0;
}