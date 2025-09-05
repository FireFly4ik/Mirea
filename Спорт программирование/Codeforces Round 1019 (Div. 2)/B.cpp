#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> answers;
    for (int test = 0; test < n; test++){
        int len;
        cin >> len;
        string s;
        cin >> s;
        char last = '0';
        int score = 0;
        bool flag = 1;
        for (int i = 0; i < len; i++){
            if (last != s[i]){
                score += 1;
                last = s[i];
            }

        }
        if (score == 2){
            score = 1;
        } else if (score > 2){
            score -= 2;
        }
        answers.push_back(score + len);
    }
    for (auto i : answers){
        cout << i << endl;
    }
    return 0;
}