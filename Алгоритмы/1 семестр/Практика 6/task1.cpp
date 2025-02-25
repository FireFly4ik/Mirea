#include <iostream>
#include <cmath>
using namespace std;

int factorial(int a){
    return (a > 1 ? factorial(a - 1) * a : 1);
}

int main(){
    int *arr, n, x;
    cin >> n;
    arr = new int [n];
    for (int i = 0; i < n; i++){
        cin >> x;
        arr[i] = x;
    }
    int a = 0, b = 0, v = 0, g = 0, d = 0, e = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] % 2 != 0){
            a++;
        }
        double square = pow(arr[i] * 1.0, 0.5);
        if ((int)square % 2 == 0 and (int)square == square){
            b++;
        }
        if (arr[i] % 3 == 0 and arr[i] % 5 != 0){
            v++;
        }
        if (pow(2.0, (i + 1) * 1.0) < arr[i] and arr[i] < factorial(i + 1)){
            g++;
        }
        if (i > 0 and i < n - 1){
            if (arr[i] < (arr[i - 1] + arr[i + 1]) /2 ){
                d++;
            }
        }
        if (arr[i] % 2 == 1 and i % 2 != 0){
            e++;
        }
    }
    cout << "а: " << a << endl;
    cout << "б: " << b << endl;
    cout << "в: " << v << endl;
    cout << "г: " << g << endl;
    cout << "д: " << d << endl;
    cout << "е: " << e << endl;
    return 0;
}