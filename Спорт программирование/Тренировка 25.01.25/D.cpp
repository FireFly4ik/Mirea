#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main(){
    int t;
    string x;
    cin >> t;
    vector<string> answers;
    for (int i = 0; i < t; i++){
        vector<int> chislo;
        cin >> x;
        for (char el : x){
            string q;
            q += el;
            chislo.push_back(stoi(q));
        }
        int flag = 1;
        while(flag != 0){
            flag = 0;
            for (int j = chislo.size() - 1; j > 0; j--){
                if (chislo[j] != 0 and chislo[j] - chislo[j - 1] > 1){
                    chislo[j]--;
                    swap(chislo[j], chislo[j - 1]);
                    flag = 1;
                }
            }
        }
        string answer = "";
        for (int j = 0; j < chislo.size(); j++){
            answer += to_string(chislo[j]);
        }
        answers.push_back(answer);
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
    return 0;
}