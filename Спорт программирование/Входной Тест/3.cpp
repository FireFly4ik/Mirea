#include <iostream>
using namespace std;

int main(){
    int p, q;
    cin >> p >> q;
    long long kolvo = 0;
    for (int i = p; i < q + 1; i++){
        for (int j = i; j < q + 1; j++){
            kolvo += min(i + j - 1, q) - j + 1;
        }
    }
    cout << kolvo << endl;
    return 0;
}