#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int a, b, c;
    cout << "Введите коэффициенты через пробел: ";
    cin >> a >> b >> c;
    string s;
    cout << "Введите символ: ";
    cin >> s;
    if (s == "P"){
        cout << "Galanov Andrey";
        return 0;
    }
    else if(s == "e"){
        if (a == 0 && b == 0 && c == 0){
            cout << "Любое действительное число";
            return 0;
        }
        int d = b * b - 4 * a * c;
        if (d == 0){
            cout << (-1) * b / (2 * a);
        }
        else if(d < 0){
            cout << "Корней нет";
        }
        else{
            cout << ((-1) * b - sqrt(d))/ (2 * a) << " " << ((-1) * b + sqrt(d))/ (2 * a);
        }
    }
    else if(s == "k"){
        int p;
        cout << "Введите число для проверки: ";
        cin >> p;
        if (p / 100000 == p % 10 && p % 100000 / 10000 == p % 100 / 10 && p % 10000 / 1000 == p % 1000 / 100){
            cout << "Число является палиндромом";
        }
        else {
            cout << "Число не является палиндромом";
        }
        return 0;
    }
    return 0;
}