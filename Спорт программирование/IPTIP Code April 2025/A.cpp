#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<long long> answer;
    for (int test = 0; test < t; test++){
        long long x;
        cin >> x;
        long long answerok = x;
        answerok += 2 * (x / 2);
        answerok += 2 * (x / 3);
        answer.push_back(answerok);
    }
    for (int test = 0; test < t; test++){
        cout << answer[test] << endl;
    }
    return 0;
}