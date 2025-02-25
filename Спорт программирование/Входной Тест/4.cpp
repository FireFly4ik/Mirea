#include <iostream>
using namespace std;

int main(){
    int n;
    long long x;
    cin >> n;
    long long *mas;
    mas = new long long[n];
    cin >> mas[0];
    for (int i = 1; i < n; i++){
        cin >> x;
        mas[i] = mas[i - 1] + x;
    }
    long long raznica = 0;
    long long minimum, maximum;
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (j == i){
                minimum = mas[i] - (i == 0 ? 0 : mas[i - 1]);
            } else {
                minimum = mas[j] - (i == 0 ? 0 : mas[i - 1]);
            }
            if (i > 0) {
                for (int k = i - 1; k > -1; k--){
                    maximum = mas[i - 1] - (k == 0 or k == i - 1 ? 0 : mas[k]);
                    if (maximum - minimum > raznica){
                        raznica = maximum - minimum;
                    }
                }
            }
            if (j < n - 1){
                for (int k = j + 1; k < n; k++){
                    maximum = mas[k] - mas[j];
                    if (maximum - minimum > raznica){
                        raznica = maximum - minimum;
                    }
                }
            }
        }
    }
    cout << raznica << endl;
    return 0;
}