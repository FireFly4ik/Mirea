#include <iostream>
using namespace std;

int main(){
    vector<vector<int>> labirint;
    for (int i = 0; i < 3; i ++){
        vector<int> push;
        for (int j = 0; j < 4; j++){
            int pushableInt;
            cin >> pushableInt;
            push.push_back(pushableInt);
        }
        labirint.push_back(push);
    }
    vector<vector<int>> stoimost;
    for (int i = 0; i < 3; i++){
        vector<int> push;
        for (int j = 0; j < 4; j++){
            push.push_back(0);
        }
        stoimost.push_back(push);
    }
    stoimost[0][0] = labirint[0][0];
    for (int i = 1; i < 4; i++){
        stoimost[0][i] = labirint[0][i] + stoimost[0][i - 1];
    }
    for (int i = 1; i < 3; i++){
        stoimost[i][0] = labirint[i][0] + stoimost[i - 1][0];
    }
    for (int j = 1; j < 3; j++){
        for (int i = 1; i < 4; i++){
            stoimost[j][i] = labirint[j][i] + max(stoimost[j - 1][i], stoimost[j][i - 1]);
        }
    }
    int i = stoimost.size() - 1, j = stoimost[0].size() - 1;
    vector<vector<int>> path;
    while (i != 0 && j != 0){
        if (stoimost[i - 1][j] > stoimost[i][j - 1]){
            path.push_back({i - 1, j});
            i--;
        } else {
            path.push_back({i, j - 1});
            j--;
        }
    }
    for (int i = path.size() - 1; i >= 0; i--){
        cout << path[i][0] << " " << path[i][1] << endl;
    }
    cout << labirint.size() - 1 << " " << labirint[0].size() - 1 << endl;
    return 0;
}