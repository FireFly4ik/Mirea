#include <iostream>
using namespace std;

int main(){
    int x;
    cin >> x;
    int arr[x - 1];
    for (int i = 0; i < x - 1; i++){
        arr[i] = i + 2;
    }
    for (int i = 0; i < x - 2; i++){
        int e = 1;
        if (e == 0){
            break;
        }
        if (arr[i] != 0){
            e = 0;
            for (int j = i + 1; j < x - 1; j++){
                if (arr[j] % arr[i] == 0){
                arr[j] = 0;
                e++;
                }
            }
        }
    }
    for (int i = 0; i <= x - 1; i++){
        if (arr[i] == x){
            cout << x << " = " << x;
            return 0;
        }
    }
    int t = 0;
    cout << x << " = ";
    for (int i = 0; i < x - 1; i++){
        int a = arr[i];
        if (a != 0 and x % a == 0){
            int e = 0;
            if (t > 0){
                cout << " * ";
            }
            while (x % a == 0 && x != 0){
                x /= a;
                e++;
            }
            cout << a << " в степени " << e;
            t += 1;
        }
        if (x == 0){
            break;
        }
    }
    cout << endl;
    return 0;
}