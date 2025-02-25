#include <iostream>
using namespace std;

int main(){
    int n, *arr, x, k = 0;
    bool dva = false, tri = false;
    cin >> n;
    arr = new int [n];
    for (int i = 0; i < n; i++){
        cin >> x;
        arr[i] = x;
    }
    for (int i = 0; i < n; i++){
        if (arr[i] == 0) {
            k++;
            if (k == 2){
                dva = true;
            }
            if (k == 3){
                tri = true;
            }
        } else {
            k = 0;
        }
    }
    cout << "dva: " << dva << endl;
    cout << "tri: " << tri << endl;
    return 0;
}