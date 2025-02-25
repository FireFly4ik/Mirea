#include <iostream>
using namespace std;
 
int main(){
    int a, h, k, m, s;
    cin>>a>>h>>k>>m>>s;
    int tempRul = s, rul = 0, ostDlin = a;
    while (tempRul >= h){
            tempRul -= (h + (h % k == 0 ? 0 : k - h % k));
            ostDlin -= m;
            if (ostDlin <= 0){
                break;
            }
        }
    rul = a / (a - ostDlin) + (a % (a - ostDlin) == 0 ? 0 : 1);
    cout << rul << endl;
    return 0;
}