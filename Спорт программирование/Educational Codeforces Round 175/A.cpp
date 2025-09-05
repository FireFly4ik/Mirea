#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        int x, k = 0;
        cin >> x;
        if (x == 0){
            cout << 1 << endl;
            continue;
        }
        k = x / 15 * 3;
        if (x % 15 >= 2){
            k += 3;
        } else if (x % 15 == 1){
            k += 2;
        } else if (x % 15 == 0){
            k++;
        }
        cout << k << endl;
    }
    return 0;
}