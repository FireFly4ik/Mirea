#include <iostream>
using namespace std;

int main(){
    int a;
    cin >> a;
    bool q;
    q = max(a / 1000, a % 10) - min(a / 1000, a % 10) + max(a % 1000 / 100, a % 100 / 10) - min(a % 1000 / 100, a % 100 / 10);
    cout << !q;
    return 0;
}