#include <iostream>
#include <array>
using namespace std;

int in(int arr[], int x, int w){
    for (int e = 0; e < w; e++){
        if (arr[e] == x){
            return 1;
        }
        if (arr[e] > x){
            return 0;
        }
    }
    return 0;
}

int main(){
    int x;
    cin >> x;
    int arr[x - 1];
    for (int i = 0; i < x - 1; i++){
        arr[i] = i + 2;
    }
    for (int i = 0; i < x - 2; i++){
        int e = 1;
        if (e == 0){
            break;
        }
        if (arr[i] != 0 && arr[i] != 1){
            e = 0;
            for (int j = i + 1; j < x - 1; j++){
                if (arr[j] % arr[i] == 0){
                arr[j] = 0;
                e++;
                }
            }
        }
    }
    if(in(arr, x, sizeof(arr)) == 1){
        cout << "Число " << x << " простое и у него один делитель - оно само ;)";
        return 0;
    }
    int m = sqrt(x);
    int q, w;
    int e = 1;
    if (x % 2 == 0){
        cout << "Число не нечетное!!!";
        return 0;
    }
    while (true){
        double y = sqrt((m + e) * (m + e) - x);
        int y1 = sqrt((m + e) * (m + e) - x);
        if (y - y1 == 0.0){
            q = (m + e - y);
            w = (m + e + y);
            break;
        }
        e++;
    }
    cout << x << " = ";
    while (in(arr, q, sizeof(arr)) == 0){
        for (int e = 0; e < x - 1; e++){
            if (q % arr[e] == 0){
                cout << arr[e] << " * ";
                q /= arr[e];
                break;
            }
        }
        
    }
    cout << q << " * ";
    while (in(arr, w, sizeof(arr)) == 0){
        for (int e = 0; e < x - 1; e++){
            if (w % arr[e] == 0){
                cout << arr[e] << " * ";
                w /= arr[e];
                break;
            }
        }
    }
    cout << w << endl;
    return 0;
}