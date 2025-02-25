#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int nums[n];
    for (int i = 1; i <= n; i ++){
        nums[i-1] = i;
    }
    for (int i = 1; i <=(n - 1) / 2; i ++){
        for (int j = i; j <= (n-1) / 2; j++ ){
            if (i + j + 2 * i * j - 1 > n){
                break;
            }
            nums[i + j + 2 * i * j - 1] = 0;
        }
    }
    for (int i = 0; i <= n; i++){
        if (nums[i] != 0){
            if (nums[i] * 2 + 1 > n){
                return 0;
            }
            cout << nums[i] * 2 + 1 << " ";
        }
    }
    return 0;
}