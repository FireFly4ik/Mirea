#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<int> answers;
    for (int i = 0; i < t; i++){
        int a, b;
        cin >> a >> b;
        if (a > b){
            answers.push_back(a);
            continue;
        }
        int x = a - (b - a);
        answers.push_back(x < 0 ? 0 : x);
        continue;
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
    return 0;
}