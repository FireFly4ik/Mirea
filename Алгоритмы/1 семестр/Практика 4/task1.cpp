#include <iostream>
using namespace std;

int f(int a, int b){
    if (a == b){
        return a;
    } else if (a > b){
        return f(a - b, b);
    } else {
        return f(a, b - a);
    }
}

int main(){
    long int a, b;
    cin >> a >> b;
    if (a == 0 and b == 0){
        cout << "Любое большое число" << endl;
        return 0;
    } else if (a == 0 or b == 0) {
        cout << (a != 0 ? abs(a) : abs(b)) << endl;
        return 0;
    }
    cout << f(abs(a), abs(b)) << endl;
    return 0;
}