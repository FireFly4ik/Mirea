#include <iostream>
using namespace std;

long long int fibonachi(long long int x){
    if (x == 1 or x == 2){
        return 1;
    }
    return (fibonachi(x - 1) + fibonachi(x - 2));
}

int main(){
    long long int x;
    cin >> x;
    cout << fibonachi(x) << endl;
    return 0;
}