#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int **mas;
    mas = new int *[n];
    for (int i = 0; i < n; i++){
        mas[i] = new int[n];
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i + j == n - 1){
                mas[i][j] = 1;
                cout << mas[i][j];
            }
            else if (i + j < n - 1){
                mas[i][j] = 0;
                cout << mas[i][j];
            }
            else {
                mas[i][j] = 2;
                cout << mas[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}