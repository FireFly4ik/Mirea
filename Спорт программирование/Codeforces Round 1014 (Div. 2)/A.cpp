#include <iostream>
#include <vector>
using namespace std;

int nod(int x, int y){
    while (x != y) {
        if (x>y) {
        x = x-y;
        }
        else {
        y = y-x;
        }
    }
    return x;
}

int main(){
    int t;
    cin >> t;
    vector<int> answers;
    for (int i = 0; i < t; i++){
        int length, maxPachka = 0, minPachka = 1000000001;
        cin >> length;
        vector<int> pachka;
        for (int j = 0; j < length; j++){
            int x;
            cin >> x;
            if (x > maxPachka) maxPachka = x;
            if (x < minPachka) minPachka = x;
            pachka.push_back(x);
        }
        answers.push_back(maxPachka - minPachka);
    }
    for (int i = 0; i < t; i++){
       cout << answers[i] << endl;
    }
    return 0;
}