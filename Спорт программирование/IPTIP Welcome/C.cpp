#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    vector<vector<long long>> answers;
    for (int i = 0; i < t; i++){
        int l;
        cin >> l;
        vector<int> first;
        for (int j = 0; j < l - 1; j++){
            int x;
            cin >> x;
            first.push_back(x);
        }
        vector<long long> answer {501};
        for (int j = 0; j < l - 1; j ++){
            answer.push_back(answer[answer.size() - 1] + first[j]);
        }
        answers.push_back(answer);
    }
    for (int i = 0; i < t; i++){
        for (int j = 0; j < answers[i].size(); j++){
            cout << answers[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}