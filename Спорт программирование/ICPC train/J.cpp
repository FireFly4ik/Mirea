#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        arr[i] = y;
    }
    int res = 0;
    int maxi = *max_element(arr.begin(), arr.end());
    int nakopleno = 1;
    for (int i = 0; i < n; i++){
        if (arr[i] > nakopleno){
            res += arr[i] - nakopleno;
            nakopleno = arr[i];
        } else if (arr[i] <= nakopleno){
            if (nakopleno < maxi){
                nakopleno++;
                res++;
            } else {
                res += n - i;
                break;
            }
        }
        if (i + 1 < arr.size()){
            if (arr[i] >= arr[i + 1]){
                res++;
                if (nakopleno < maxi){
                    nakopleno++;
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}