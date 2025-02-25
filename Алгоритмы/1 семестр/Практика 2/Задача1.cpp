#include <iostream>
#include <math.h>
using namespace std;

int nod(int a, int b){
    while (max(a, b) % min(a,b) != 0){
        if (a == 0 || b == 0){
            return max(a, b);
        }
        if (a >= b){
            a = a % b;
        }
        else {
            b = b % a;
        }
    }
    return min(a, b);
}

int main(){
    int a, b, c;
    cout << "Введите числа через пробел: \n";
    cin >> a >> b >> c;
    int d = nod(nod(abs(a), abs(b)), nod(abs(b), abs(c)));
    if (a == 0 and b == 0 and c == 0){
        cout << "Любое большое число";
    }
    else{
        cout << d;
    }
    return 0;
}