#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> answers;
    for (int test = 0; test < n; test++){
        int len, k;
        cin >> len >> k;
        vector<int> mas;
        int a;
        cin >> a;
        mas.push_back(a > k ? -1 : 1);
        for (int i = 1; i < len; i++){
            cin >> a;
            mas.push_back(mas[i -1] + (a > k ? -1 : 1));
        }
        bool flag = false;
        for (int i = 0; i < len - 2; i++){
            for (int j = i + 1; j < len - 1;j++){
                int sum1 = mas[i] - mas[0], sum2 = mas[j] - mas[i], sum3 = mas[len - 1] - mas[j];
                vector<int> answ {sum1, sum2, sum3};
                sort(answ.begin(), answ.end());
                if (answ[1] > 0){
                    answers.push_back(1);
                    flag = true;
                    break;
                }
            }
            if (flag){
                break;
            }
        }
        if (!flag){
            answers.push_back(0);
        }
    }
    for (auto i : answers){
        if (i == 0){
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}