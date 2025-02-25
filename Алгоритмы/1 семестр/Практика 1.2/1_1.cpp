#include <iostream>
#include <array>
using namespace std;

int binar(int *arr,int x){
    int l(0);
    int r(sizeof(arr) - 2);
    while (l <= r){
        int q((r + l) / 2);
        cout << q << " " << l << " " << r << "\n";
        if (x == arr[q]){
            return q;
        }
        else if (x < arr[q]){
            r = q;
        }
        else{
            l = q;
        }
        if (r - l == 1){
            return l;
        }
    }
    return 0;
}

int main(){
    int values[]{1,2,3,5,6,7};
    cout <<  - 1 << "\n";
    /*cout << binar(values, 7);
    cout << binar(values, 4);
    cout << binar(values, 8);*/
}