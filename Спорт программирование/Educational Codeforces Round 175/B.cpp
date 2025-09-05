#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int t;
    cin >> t;
    for (int povt = 0; povt < t; povt++){
        long long n, x, k;
        long long answ = 0;
        cin >> n >> x >> k;
        string stroka;
        cin >> stroka;
        vector<int> smeshenie {0};
        for (int i = 0; i < n; i++){
            if (x > 0){
                if (stroka[i] == 'L'){
                    smeshenie.push_back(smeshenie[smeshenie.size() - 1] + 1);
                } else {
                    smeshenie.push_back(smeshenie[smeshenie.size() - 1] - 1);
                }
            } else if (x < 0) {
                if (stroka[i] == 'L'){
                    smeshenie.push_back(smeshenie[smeshenie.size() - 1] - 1);
                } else {
                    smeshenie.push_back(smeshenie[smeshenie.size() - 1] + 1);
                }
            }
        }
        smeshenie.erase(smeshenie.begin());
        int maxStep = *max_element(smeshenie.begin(), smeshenie.end());
        int indMax = n - 1, indNul = n;
        for (int i = 0; i < n - 1; i++){
            if (smeshenie[i] == maxStep){
                indMax = i;
            }
            if (smeshenie[i] == 0 and indNul == n){
                indNul = i;
            }
        }
        if (x != 0) {
            if (smeshenie[n - 1] == 0 and indNul == n) {
                indNul = n - 1;
            }
            k = k - n * ((abs(x) - maxStep) / smeshenie[n - 1]) - indMax - 1;
            if (k < 0){
                cout << 0 << endl;
                continue;
            } else if (k == 0) {
                cout << 1 << endl;
                continue;
            }
            answ ++;
        }
        if (indNul != n) {
            answ += k / (indNul + 1);
        }
        cout << answ << endl;
    }
}