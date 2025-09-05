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
        string a, b;
        cin >> a >> b;
        int podtests;
        cin >> podtests;
        for (int podtest = 0; podtest < podtests; podtest++){
            int answerok = 0;
            int l, r;
            cin >> l >> r;
            string a1 = a.substr(l - 1, r - l + 1);
            string b1 = b.substr(l - 1, r - l + 1);
            if (r - l + 1 > 2){
                for (int i = 0; i < a1.size() - 2; i++) {
                    if (a1[i] == '0' and a1[i + 2] == '0'){
                        b1[i + 1] = '1';
                    }
                }
                for (int i = 0; i < a1.size() - 2; i++) {
                    if (b1[i] == '1' and b1[i + 2] == '1'){
                        a1[i + 1] = '1';
                    }
                }
            }
            for (int i = 0; i < a1.size(); i++){
                if (a1[i] == '1'){
                    answerok++;
                }
            }
            answer.push_back(answerok);
        }
    }
    for (int test = 0; test < answer.size(); test++){
        cout << answer[test] << endl;
    }
    return 0;
}