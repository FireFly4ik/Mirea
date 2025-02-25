#include <iostream>
using namespace std;

int solving(int n, int start, int finish, int bufer){
    int k = 0;
    if (n != 0){
        k += solving(n - 1, start, bufer, finish);
        cout << "Бублик "<< n << " со штыря " << start <<  " на штырек " << finish << endl;
        k += 1;
        k += solving(n - 1, bufer, finish, start);
    }
    if (n == 1){
        return 1;
    }
    return k;
}

int main(){
    int n;
    cout << "Введите количество дисков: ";
    cin >> n;
    cout << solving(n, 1, 3, 2) << endl;
    return 0;
}