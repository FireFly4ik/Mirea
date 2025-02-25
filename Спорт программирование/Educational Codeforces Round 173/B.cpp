#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

unsigned long long factorial(long long n){
    if (n == 1){
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

void solve(){
    int number;
    cin >> number;
    vector<vector<unsigned long long>> mainAnswer;
    for (int i = 0; i < number; i++){
        vector<unsigned long long> answer {1};
        unsigned long long n, chislo = 0, sum = 0;
        int d;
        cin >> n >> d;
        sum = d * factorial(n);
        if (sum % 3 == 0){
            answer.push_back(3);
        }
        if (d == 0 or d == 5){
            answer.push_back(5);
        }
        if (d == 7 or n >= 3){
            answer.push_back(7);
        }
        if (sum % 9 == 0){
            answer.push_back(9);
        }
        mainAnswer.push_back(answer);
    }
    for (int i = 0; i < number; i++){
        for (unsigned long long j = 0; j < mainAnswer[i].size(); j++){
            cout << mainAnswer[i][j];
            if (j != mainAnswer[i].size() - 1){
                cout << " ";
            } else {
                cout << endl;
            }
        }
    }
}

int main(){
    solve();
    return 0;
}