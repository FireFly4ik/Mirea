#include <iostream>
using namespace std;

int main(){
    int n, maximum = 0, x, zayavka = 0;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> x;
        if (x > maximum){
            maximum = x;
        }
        zayavka += x;
    }
    cout << zayavka - maximum + n + 1 << endl;
    return 0;
}