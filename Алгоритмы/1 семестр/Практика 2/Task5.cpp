#include <iostream>
using namespace std;

int main(){
    long long int nach = 78310;
    cout << 1 << " " << nach << "\n";
    for (int i = 0; i < 9; i++){
        nach = pow(nach, 3);
        nach = nach % 100000000 / 1000;
        while (nach < 10000){
            nach *= 13;
        }
        cout << i+2 << " " << nach << "\n";
    }
    return 0;
}