#include <iostream>
using namespace std;

long long f(long long x){
    if (x / 10 > 0){
        return x % 10 + f(x / 10);
    }
    return x;
}

int main(){
    long long x;
    cin >> x;
    cout << f(x) << endl;
    return 0;
}