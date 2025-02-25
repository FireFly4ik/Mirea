#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t, a1, a2, a4, a5;
    cin >> t;
    vector<int> answers;
    for (int i = 0; i < t; i++){
        cin >> a1 >> a2 >> a4 >> a5;
        if ((a1 + a2) == (a4 - a2) and (a1 + a2) == (a5 - a4)){
            answers.push_back(3);
        } else if ((a1 + a2 == a4 - a2) or (a1 + a2 == a5 - a4) or (a4 - a2 == a5 - a4)){
            answers.push_back(2);
        } else {
            answers.push_back(1);
        }
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
}