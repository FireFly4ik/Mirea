#include <iostream>
#include <vector>
#include <string>
using namespace std;

string solve(int n, int a, int b){
    if (abs(a - b) % 2 == 1){
        return "NO";
    } else {
        return "YES";
    }
}

int main(){
    int t, n, a, b;
    vector<string> answer;
    cin >> t;
    for (int i = 0; i < t; i++){
        cin >> n >> a >> b;
        answer.insert(answer.end(), solve(n, a, b));
    }
    for (int i = 0; i < t; i++){
        cout << answer[i] << endl;
    }
}