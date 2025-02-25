#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int t, n;
    string stroka;
    vector<vector<int>> answers;
    cin >> t;
    for (int i = 0; i < t; i++){
        answers.push_back({1});
        cin >> n;
        for (int j = 0; j < n; j++){
            cin >> stroka;
            if (j == 0){continue;}
            for (int k = answers[i].size() - 1; k >= 0; k--){
                if (stroka[answers[i][k] - 1] == '0'){
                    continue;
                } else {
                    answers[i].insert(answers[i].begin() + k + 1, j + 1);
                    break;
                }
            }
            if (answers[i].size() == j){
                answers[i].insert(answers[i].begin(), j + 1);
            }
        }
    }
    for (int i = 0; i < t; i++){
        for (int j = 0; j < answers[i].size(); j++){
            cout << answers[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}