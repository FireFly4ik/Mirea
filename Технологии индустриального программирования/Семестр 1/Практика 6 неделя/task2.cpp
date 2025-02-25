#include <iostream>
using namespace std;

int main(){
    int dl, v;
    cin >> dl >> v;
    char **mas;
    mas = new char* [v];
    for (int i = 0; i < dl; i ++){
        mas[i] = new char[v];
    }
    int kol;
    cin >> kol;
    for (int i = 0; i < kol; i++){
        int x, y;
        cin >> x >> y;
        mas[x - 1][y - 1] = '*';
    }
    for (int i = 0; i < dl; i++){
        for (int j = 0; j < v; j++){
            if (mas[i][j] != '*'){
                int k = 0;
                for (int q = i - 1; q <= i + 1; q++){
                    if (q >= 0 and q < dl){
                        for (int w = j - 1; w <= j + 1; w++){
                            if (w >= 0 and w < v){
                                if ((w != j or q != i) and mas[q][w] == '*'){
                                    k += 1;
                                }
                            }
                        }
                    }
                }
                cout << k;
            }
            else{
            cout << mas[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}