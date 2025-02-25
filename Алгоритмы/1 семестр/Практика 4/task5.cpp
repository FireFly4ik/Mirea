#include <iostream>
using namespace std;

long long f(long long x){
    if (x == 1) {
        return 1;
    } else if (x % 2 == 0){
        return f(x / 2);
    } else {
        return f(x / 2) + f(x / 2 + 1);
    }
}

int main(){
    long long x;
    cin >> x;
    cout << f(x) << endl;
    return 0;
}