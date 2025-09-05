#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> answ(N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            cin >> x;
            if (i != j) {
                answ[i] |= x;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << answ[i] << " ";
    }

    return 0;
}