#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t, x, n;
    int flag;
    cin >> t;
    vector<int> answers;
    for (int i = 0; i < t; i++){
        flag = 1;
        cin >> n;
        vector<int> mas;
        vector<int> maska;
        for(int j = 0; j < n; j++){
            cin >> x;
            mas.push_back(x);
            if (j > 1){
                if ((abs(mas[j - 1] - mas[j - 2]) == x or (mas[j-1] + mas[j-2] == x)) and flag != 0){
                    flag = 1;
                } else {
                    flag = 0;
                }
            }
        }
        answers.push_back(flag);
    }
    for (int i = 0; i < t; i++){
        if (answers[i] == 0){
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
}