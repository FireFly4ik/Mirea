#include <iostream>
#include <vector>
using namespace std;

void solve(){
    long long numberOFMonets;
    cin >> numberOFMonets;
    vector<long long> answers;
    for (unsigned long long i = 0; i < numberOFMonets; i++){
        unsigned long long x, k = 1;
        cin >> x;
        while (x > 3){
            k *= 2;
            x /= 4;
        }
        answers.push_back(k);
    }
    for (unsigned long long i = 0; i < answers.size(); i++){
        cout << answers[i] << endl;
    }
}

int main(){
    solve();
    return 0;
}