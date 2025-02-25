#include <iostream>
using namespace std;

int main(){
    int x, y;
    cin >> x;
    cin >> y;
    int e = 0;
    cout << x;
    while (x > y){
        e++;
        if (x % 2 == 0 and x / 2 >= y){
            x /= 2;
            cout << " / 2 = " << x;
            continue;
        }
        x -= 1;
        cout << " - 1 = " << x;
    }
    cout << "\n";
    cout << e << " шагов";
}