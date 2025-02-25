#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;

int main(){
    int t, x, k, n;
    cin >> t;
    vector<int> answers;
    for (int i = 0; i < t; i++){
        map<int, int> mapa;
        set<int> keys;
        k = 0;
        cin >> n;
        for (int j = 0; j < n; j++){
            cin >> x;
            if (keys.count(x) == 0){
                keys.insert(x);
                mapa[x] = 1;
            } else {
                mapa[x]++;
            }
        }
        for (int el : keys){
            if (mapa[el] % 2 == 0){
                k += mapa[el] / 2;
            }
        }
        answers.push_back(k);
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
    return 0;
}