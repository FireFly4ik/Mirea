#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    unsigned long long t, n, x, k, maxOtd, neobh;
    vector<string> answer;
    vector<int> materials;
    cin >> t;
    for (int i = 0; i < t; i++){
        materials.clear();
        k = neobh = 0;
        maxOtd = 1000000001;
        cin >> n;
        for (int j = 0; j < n; j++){
            cin >> x;
            materials.insert(materials.end(), x);
        }
        for (int j = 0; j < n; j++){
            cin >> x;
            if (materials[j] < x){
                k++;
                neobh = max(neobh, x - materials[j]);
            } else {
                maxOtd = min(maxOtd, materials[j] - x);
            }
        }
        if (k > 1 or neobh > maxOtd){
            answer.insert(answer.end(), "NO");
        } else {
            answer.insert(answer.end(), "YES");
        }
    }
    for (int i = 0; i < t; i++){
        cout << answer[i] << endl;
    }
}