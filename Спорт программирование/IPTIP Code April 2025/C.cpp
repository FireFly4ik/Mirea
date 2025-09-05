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
        vector<vector<char>> a;
        for (int i = 0; i < n; i++){
            a.push_back(vector<char>());
            for (int j = 0; j < n; j++){
                char x;
                cin >> x;
                a[i].push_back(x);
            }
        }
        int answerok = 0;
        for (int i = 0; i < n - 1; i++){
            for (int j = 0; j <= ((n - 1) / 2 >= i ? i : n - 1 - i - !(n % 2)); j++){
                char maxChar = max(a[i][j], max(a[n - 1 - j][i], max(a[j][n - 1 - i], a[n - 1 - i][n - 1 - j])));
                answerok += (maxChar - a[i][j]) + (maxChar - a[n - 1 - j][i]) + (maxChar - a[j][n - 1 - i]) + (maxChar - a[n - 1 - i][n - 1 - j]);
            }   
        }
        answer.push_back(answerok);
    }
    for (int test = 0; test < t; test++){
        cout << answer[test] << endl;
    }
    return 0;
}