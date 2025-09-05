#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, x, y;
    cin >> n;
    cin >> x >> y;
    vector<int> arr, un;
    un.push_back(INT_MAX);
    
    for(int i= 0; i < n; i++) {
        int t;
        cin>>t;
        arr.push_back(t);
    }
    sort (arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        if (arr[i] > x && arr[i] < y && arr[i] != un[un.size()-1]) {
            un.push_back(arr[i]);
        }
    }
    cout << un.size() - 1 << endl;
    return 0;

}