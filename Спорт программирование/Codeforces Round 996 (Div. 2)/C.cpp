#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
    unsigned long long tasks, n, m, element;
    string tray;
    vector<vector<int>> setka; 
    vector<string> answer;
    cin >> tasks;
    for (int taskNumber = 0; taskNumber < tasks; taskNumber++){
        cin >> tray >> n >> m;
        for(int i = 0; i < n; i++){
            vector<int> nullVector;
            setka.insert(setka.end(), nullVector);
            for(int j = 0; j < m; j++){
                cin >> element;
                setka[i].push_back(element);
            }
        }
    }
}