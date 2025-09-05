#include <iostream>
#include <algorithm>
using namespace std;

int solve (vector<pair<int, int>>* tasks){
    int startOfDay = 600, endofDay = 1200;
    int answ = 0;
    sort(tasks->begin(), tasks->end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    int last = 599;
    for (int i = 0; i < tasks->size(); i++){
        if ((*tasks)[i]. first >= last) {
            if ((*tasks)[i].first < startOfDay) {
                continue;
            }
            if ((*tasks)[i].second > endofDay){
                break;
            }
            answ++;
            last = (*tasks)[i].second;
        }
    }
    return answ;
} 

int main(){
    vector<vector<pair<int, int>>> testCases = {
        {{600, 700}, {710, 800}, {810, 900}, {901, 1000}},       // 4
        {{600, 900}, {700, 1000}, {800, 1100}},                  // 1
        {{500, 700}, {700, 900}, {900, 1300}},                   // 1
        {{600, 700}, {700, 800}, {800, 900}, {900, 1000}},       // 4
        {{600, 700}, {600, 700}, {600, 700}},                    // 1
        {},                                                      // 0
        {{800, 1000}},                                           // 1
        {{1201, 1300}}                                           // 0
    };

    for (int i = 0; i < testCases.size(); ++i) {
        int result = solve(&testCases[i]);
        cout << "Test " << i + 1 << ": " << result << endl;
    }
}