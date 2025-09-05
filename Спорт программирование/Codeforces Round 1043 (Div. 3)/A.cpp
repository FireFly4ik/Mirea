#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<string> answers;
    for (int i = 0; i < t; i++){
        string start, add, ochered;
        int dlA, dlB;
        cin >> dlA >> start >> dlB >> add >> ochered;
        string result = start;
        for (int i = 0; i < dlB; i++) {
            if (ochered[i] == 'D') {
                result += add[i];
            } else {
                result = add[i] + result;
            }
        }
        answers.push_back(result);
    }
    for (int i = 0; i < t; i++){
       cout << answers[i] << endl;
    }
    return 0;
}