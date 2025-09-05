#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> answers;
    for (int test = 0; test < n; test++){
        int len;
        cin >> len;
        map<int, int> mas;
        for (int i = 0; i < len; i++){
            int a;
            cin >> a;
            mas[a] += 1;
        }
        answers.push_back(mas.size());
    }
    for (auto i : answers){
        cout << i << endl;
    }
    return 0;
}