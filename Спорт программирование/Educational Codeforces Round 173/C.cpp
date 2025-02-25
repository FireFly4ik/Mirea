#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void solve(){
    int numberOfTests;
    cin >> numberOfTests;
    vector<set<long long>> answer;
    for(int i = 0; i < numberOfTests; i++){
        answer.push_back({0});
        long long len, x;
        vector<long long> vec;
        cin >> len >> x;
        vec.push_back(x);
        answer[i].insert(x);
        for (long long j = 1; j < len; j++){
            cin >> x;
            vec.push_back(x + vec[j-1]);
            answer[i].insert(x);
            answer[i].insert(x + vec[j-1]);
        }
        for (long long j = 0; j < len - 1; j++){
            for (long long k = j + 1; k < len; k++){
                answer[i].insert(vec[k] - vec[j]);
            }
        }
    }
    for (int i = 0; i < numberOfTests; i++){
        vector<long long> answ {answer[i].begin(), answer[i].end()};
        //sort(answ.begin(), answ.end());
        cout << answ.size() << endl;
        for (long long j = 0; j < answ.size(); j++){
            cout << answ[j];
            if (j != answ.size() - 1){
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