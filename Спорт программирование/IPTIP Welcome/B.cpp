#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    vector<int> answers(t);
    
    for (int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;
        
        unordered_map<int, int> brendMoney;
        
        for (int j = 0; j < k; j++) {
            int brend, money;
            cin >> brend >> money;
            brendMoney[brend] += money;
        }
        
        priority_queue<int> pq;
        for (const auto& entry : brendMoney) {
            pq.push(entry.second);
        }
        
        int answer = 0;
        for (int x = 0; x < n && !pq.empty(); x++) {
            answer += pq.top();
            pq.pop();
        }
        
        answers[i] = answer;
    }
    
    for (const int& ans : answers) {
        cout << ans << endl;
    }
    
    return 0;
}
