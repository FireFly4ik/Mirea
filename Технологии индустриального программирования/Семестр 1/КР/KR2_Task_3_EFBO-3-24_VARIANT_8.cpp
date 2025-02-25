//Group: EFBO-03-24
//Student: Galanov Andrey

#include <iostream>
using namespace std;

long long int f(long long int a, long long int b){
    return (a > b ? a : b);
}

int main(){
    long long int a, b;
    cin >> a >> b;
    cout << f(a, b) << endl;
    return 0;
}