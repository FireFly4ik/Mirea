#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(){
    int t, dvoek, troek, sum;
    string x;
    cin >> t;
    vector<int> answers;
    for (int i = 0; i < t; i++){
        dvoek = troek = 0;
        sum = 0;
        cin >> x;
        for (char el : x){
            string q;
            q += el;
            sum += stoi(q);
            if (q == "2"){
                dvoek++;
            }
            if (q == "3"){
                troek++;
            }
        }
        set<int> variations{sum % 9};
        int flag = (sum % 9 == 0);
        for (int j = 0; j < dvoek; j++){
            if (flag == 1){
                break;
            }
            set<int> temp(variations.begin(), variations.end());
            for (int el : temp){
                if ((el + 2) % 9 == 0){
                    flag = 1;
                    break;
                }
                variations.insert((el + 2) % 9);
            }
        }
        for (int j = 0; j < troek; j++){
            if (flag == 1){
                break;
            }
            set<int> temp(variations.begin(), variations.end());
            for (int el : temp){
                if ((el + 6) % 9 == 0){
                    flag = 1;
                    break;
                }
                variations.insert((el + 6) % 9);
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
    return 0;
}