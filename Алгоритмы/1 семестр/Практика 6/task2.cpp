#include <iostream>
using namespace std;

int main(){
    int n, *arr, x, k = 0, sum = 0;
    cin >> n;
    arr = new int [n];
    for (int i = 0; i < n; i ++){
        cin >> x;
        arr[i] = x;
        if (x % 5 == 0 and x % 7 != 0){
            sum += x;
            k++;
        }
    }
    cout << sum << " " << k << endl;
    return 0;
}