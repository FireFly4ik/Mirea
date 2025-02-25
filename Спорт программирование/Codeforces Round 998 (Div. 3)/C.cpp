#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> answers, game;
    int t, n, k, l, r, x, q;
    cin >> t;
    for (int i = 0; i < t; i++){
        q = 0;
        game.clear();
        cin >> n >> k;
        l = 0; r = n - 1;
        for (int j = 0; j < n; j++){
            cin >> x;
            game.push_back(x);
        }
        sort(game.begin(), game.end());
        if (game[l] >= k){
            answers.push_back(0);
            continue;
        }
        while (game[r] > k){
            r--;
        }
        while (r > l){
            while (game[l] + game[r] < k and l < r){
                l++;
            }
            if (l == r){
                break;
            }
            if (game[r] + game[l] == k){
                q++;
                l++;
            }
            r--;
        }
        answers.push_back(q);
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
}