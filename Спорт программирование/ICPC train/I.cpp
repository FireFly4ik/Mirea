#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

unsigned long long mod = 1000000007;

long long factorial(long long x, vector<unsigned long long>* factorials){
    if (x < (*factorials).size()){
        return (*factorials)[x];
    } else {
        (*factorials).push_back((*factorials)[x - 1] * x % mod);
        return (*factorials)[x];
    }
}

int main(){
    vector<unsigned long long> forms{1, 1};
    vector<unsigned long long> factorials{1,1,2};
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    vector<long long> answ;
    cin >> t;
    for (int test = 0; test < t; test++){
        int x;
        cin >> x;
        if (x >= forms.size()){
            for (int i = forms.size() - 1; i <= x; i++){
                forms.push_back(forms[forms.size() - 1] * factorial(i + 1, &factorials) % mod);
            }
        }
        answ.push_back(forms[x]);
    }
    for (int i = 0; i < t; i++){
        cout << answ[i] << endl;
    }
    return 0;
}