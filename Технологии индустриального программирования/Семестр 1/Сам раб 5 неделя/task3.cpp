#include <iostream>
using namespace std;

int main(){
    int n;
    int* mas;
    cout << "Введите количество учеников: \n";
    cin >> n;
    int kol = 0;
    mas = new int[n];
    for (int i = 0; i < n; i++){
        int e;
        cout << "Введите номер пары с которой хочет уйти ученик " << i + 1 << "\n";
        cin >> e;
        mas[i] = e;
    }
    int pred = 0;
    for (int i = 1; i < n; i++){
        if (pred == -1){
            pred = i;
            continue;
        }
        if (mas[i] == mas[pred]){
            mas[i] = 0;
            mas[pred] = 0;
            kol += 2;
            for (int j = pred - 1; j > -1; j--){
                if (mas[j] != 0){
                    pred = j;
                    break;
                }
            }
            if (mas[pred] == 0){
                pred = -1;
            }
        } else {
            pred = i;
        }
    }
    cout << "\nУшло " << kol << " боссов KFC";
    return 0;
}