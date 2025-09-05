#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

bool glas(char a){
    return (a == 'a' or a == 'e' or a == 'i' or a == 'o' or a == 'u' or a == 'y');
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string slovo;
    cin >> slovo;
    bool flag = false;
    for (int i = 0; i < slovo.size() - 2; i++){
        if ((glas(slovo[i]) == glas(slovo[i + 1])) and (glas(slovo[i + 1]) == glas(slovo[i + 2]))){
            flag = true;
            break;
        }
    }
    if (flag){
        cout << "BAD" << endl;
    } else {
        cout << "GOOD" << endl;
    }
    return 0;
}