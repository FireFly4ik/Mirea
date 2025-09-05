#include <iostream>
#include <string>
using namespace std;

int countNines(const string& s) {
    int cnt = 0;
    for (char c : s) {
        if (c == '9') cnt++;
    }
    return cnt;
}

string subtractOne(string s) {
    int i = s.size() - 1;
    while (i >= 0 && s[i] == '0') {
        s[i] = '9';
        i--;
    }
    if (i >= 0) {
        s[i]--;
    }
    if (s[0] == '0' && s.size() > 1) {
        s.erase(0, 1);
    }
    return s;
}

int main() {
    int n;
    cin >> n;
    long long answer = 0;

    for (int i = 0; i < n; i++) {
        string price;
        cin >> price;

        int oldNines = countNines(price);

        string newPrice = subtractOne(price) + ".99";
        int newNines = countNines(newPrice);

        answer += (newNines - oldNines);
    }

    cout << answer << endl;
    return 0;
}