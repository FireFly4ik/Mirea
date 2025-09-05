#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t, k, p;
    cin >> t >> k >> p;
    if (t <= p * k)
    {
        cout << t / k << endl;
    }
    else
    {
        cout << t - p * k + p << endl;
    }
    return 0;
}