#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t, n, m, x;
    vector<int> hod, ochered;
    vector<vector<int>> answers;
    cin >> t;
    for (int i = 0; i < t; i++){
        cin >> n >> m;
        answers.push_back({});
        if (n == 1){
            for (int j = 0; j < m; j++){
                cin >> x;
            }
            answers[i].push_back(1);
            continue;
        }
        ochered.clear();
        for (int j = 0; j < n; j++){
            hod.clear();
            for (int k = 0; k < m; k++){
                cin >> x;
                if (hod.size() != 0 and x % n != hod[hod.size() - 1] % n){
                    answers[i].push_back(-1);
                    for (int l = 0; l < m - 1 - k + m * (n - 1 - j); l++){
                        cin >> x;
                    }
                    break;
                } else {
                    hod.push_back(x);
                }
            }
            if (answers[i].size() == 1){
                break;
            }
            ochered.push_back(hod[0] % n);
        }
        for (int j = 0; j < n; j++){
            if (answers[i].size() == 1 and answers[i][0] == -1){
                break;
            }
            for (int k = 0; k < ochered.size(); k++){
                if (ochered[k] == j){
                    answers[i].push_back(k + 1);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < t; i++){
        for (int j = 0; j < answers[i].size(); j++){
            cout << answers[i][j] << ' ';
        }
        cout << endl;
    }
}