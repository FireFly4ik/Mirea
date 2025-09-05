#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main(){
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        unsigned long long chislo;
        cin >> chislo;
        unsigned long long count = 0;
        unsigned long long stepen = 1;
        vector<unsigned long long> answers;
        for (int j = 1; j <= 18; j++) {
            stepen *= 10;
            unsigned long long predpolozhenie = chislo / (stepen + 1);
            if (predpolozhenie == 0) {
                break;
            }
            if (predpolozhenie * (stepen + 1) == chislo) {
                count++;
                answers.emplace(answers.begin(), predpolozhenie);
            }
        }
        if (count == 0) {
            cout << "0" << endl;
            continue;
        } else {
            cout << count << endl;
        }
        for (int j = 0; j < count; j++) {
            cout << answers[j] << " ";
        }
        cout << endl;
    }
    return 0;
}