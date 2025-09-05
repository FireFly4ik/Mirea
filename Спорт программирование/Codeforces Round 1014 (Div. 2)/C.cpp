#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<int> answers;
    for (int i = 0; i < t; i++){
        int chet=0, nechet=0, summa=0, maxChet = 0, maxNechet = 0;
        int length;
        cin >> length;
        for (int j = 0; j < length; j++){
            int x;
            cin >> x;
            if (x % 2 == 1){
                nechet++;
                maxNechet = max(maxNechet, x);
            } else {
                maxChet = max(maxChet, x);
                chet++;
            }
            summa += x;
        }
        if (chet == 0){
            answers.push_back(maxNechet);
            continue;
        }
        if (nechet == 0){
            answers.push_back(maxChet);
            continue;
        }
        answers.push_back(summa - min(chet, nechet) + (chet % 2 == nechet % 2));
    }
    for (int i = 0; i < t; i ++){
        cout << answers[i] << endl;
    }
    return 0;
}