#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<long long> answer;
    for (int test = 0; test < t; test++){
        int n;
        cin >> n;
        vector<int> a;
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            a.push_back(x);
        }
        bool flag = 0;
        if (n % 2 == 1){
            for (int i = 0; i < n - 1; i++){
                if (a[i] >= a[i + 1]){
                    flag = 1;
                    break;
                }
            }
        } else {
            flag = 1;
        }
        answer.push_back(flag);
    }
    for (int test = 0; test < t; test++){
        cout << (answer[test] ? "YES" : "NO") << endl;
    }
    return 0;
}