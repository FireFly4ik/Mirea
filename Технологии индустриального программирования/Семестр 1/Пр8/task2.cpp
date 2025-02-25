#include <iostream>
using namespace std;

int NOD(int a, int b){
    if (b == 0){
        return a;
    }
    return NOD(b, a % b);
}

int main(){
    int a, b;
    cin >> a >> b;
    cout << NOD(max(abs(a), abs(b)), min(abs(a), abs(b))) << endl;
    return 0;
}