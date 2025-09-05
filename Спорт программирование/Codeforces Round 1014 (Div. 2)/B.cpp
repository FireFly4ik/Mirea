#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<string> answers;
    for (int i = 0; i < t; i++){
        int length;
        cin >> length;
        string first, second;
        cin >> first >> second;
        int chetFirst = 0, chetSecond = 0, nechetFirst = 0, nechetSecond = 0;
        for (int j = 0; j < length; j++){
            if (first[j] == '1'){
                if (j % 2 == 1){
                    nechetFirst++;
                } else {
                    chetFirst++;
                }
            }
            if (second[j] == '0'){
                if (j % 2 == 1){
                    nechetSecond++;
                } else {
                    chetSecond++;
                }
            }
        }
        nechetFirst -= chetSecond;
        chetFirst -= nechetSecond;
        if (chetFirst <= 0 and nechetFirst <= 0){
            answers.push_back("YES");
        } else {
            answers.push_back("NO");
        }
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
    return 0;
}