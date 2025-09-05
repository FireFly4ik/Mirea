#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        int n;
        cin >> n;
        char mast;
        cin >> mast;
        vector<pair<char, vector<string>>> deck {{'C', {}}, {'H', {}}, {'D', {}}, {'S', {}}};
        for (int j = 0; j < n * 2; j++){
            string x;
            cin >> x;
            if (x[1] == 'C'){
                deck[0].second.push_back(x);
            } else if (x[1] == 'H'){
                deck[1].second.push_back(x);
            } else if (x[1] == 'D'){
                deck[2].second.push_back(x);
            } else {
                deck[3].second.push_back(x);
            }
        }
        int c = deck[0].second.size();
        int h = deck[1].second.size();
        int d = deck[2].second.size();
        int s = deck[3].second.size();
        if (mast == 'C') {
            if (((c - h % 2 - d % 2 - s % 2) % 2 == 1) or ((c - h % 2 - d % 2 - s % 2) < 0)){
                cout << "IMPOSSIBLE" << endl;
                continue;
            }
        } else if (mast == 'H') {
            if (((h - c % 2 - d % 2 - s % 2) % 2 == 1) or ((h - c % 2 - d % 2 - s % 2) < 0)){
                cout << "IMPOSSIBLE" << endl;
                continue;
            }
        } else if (mast == 'D') {
            if (((d - h % 2 - c % 2 - s % 2) % 2 == 1) or ((d - h % 2 - c % 2 - s % 2) < 0)){
                cout << "IMPOSSIBLE" << endl;
                continue;
            }
        } else {
            if (((s - h % 2 - d % 2 - c % 2) % 2 == 1) or ((s - h % 2 - d % 2 - c % 2) < 0)){
                cout << "IMPOSSIBLE" << endl;
                continue;
            }
        }
        sort(deck[0].second.begin(), deck[0].second.end());
        sort(deck[1].second.begin(), deck[1].second.end());
        sort(deck[2].second.begin(), deck[2].second.end());
        sort(deck[3].second.begin(), deck[3].second.end());
        if (mast != 'C') {
            while (deck[0].second.size() >= 2){
                cout << deck[0].second[0] << " " << deck[0].second[1] << endl;
                deck[0].second.erase(deck[0].second.begin());
                deck[0].second.erase(deck[0].second.begin());
            }
        }
        if (mast != 'H') {
            while (deck[1].second.size() >= 2){
                cout << deck[1].second[0] << " " << deck[1].second[1] << endl;
                deck[1].second.erase(deck[1].second.begin());
                deck[1].second.erase(deck[1].second.begin());
            }
        }
        if (mast != 'D') {
            while (deck[2].second.size() >= 2){
                cout << deck[2].second[0] << " " << deck[2].second[1] << endl;
                deck[2].second.erase(deck[2].second.begin());
                deck[2].second.erase(deck[2].second.begin());
            }
        }
        if (mast != 'S'){
            while (deck[3].second.size() >= 2){
                cout << deck[3].second[0] << " " << deck[3].second[1] << endl;
                deck[3].second.erase(deck[3].second.begin());
                deck[3].second.erase(deck[3].second.begin());
            }
        }
        if (mast == 'C') {
            while (deck[1].second.size() > 0) {
                cout << deck[1].second[0] << " " << deck[0].second.front() << endl;
                deck[1].second.erase(deck[1].second.begin());
                deck[0].second.erase(deck[0].second.begin());
            }
            while (deck[2].second.size() > 0) {
                cout << deck[2].second.front() << " " << deck[0].second.front() << endl;
                deck[2].second.erase(deck[2].second.begin());
                deck[0].second.erase(deck[0].second.begin());
            }
            while (deck[3].second.size() > 0) {
                cout << deck[3].second.front() << " " << deck[0].second.front() << endl;
                deck[3].second.erase(deck[3].second.begin());
                deck[0].second.erase(deck[0].second.begin());
            }
            while (deck[0].second.size() >= 2){
                cout << deck[0].second[0] << " " << deck[0].second[1] << endl;
                deck[0].second.erase(deck[0].second.begin());
                deck[0].second.erase(deck[0].second.begin());
            }
        } else if (mast == 'H') {
            while (deck[0].second.size() > 0) {
                cout << deck[0].second.front() << " " << deck[1].second.front() << endl;
                deck[0].second.erase(deck[0].second.begin());
                deck[1].second.erase(deck[1].second.begin());
            }
            while (deck[2].second.size() > 0) {
                cout << deck[2].second.front() << " " << deck[1].second.front() << endl;
                deck[2].second.erase(deck[2].second.begin());
                deck[1].second.erase(deck[1].second.begin());
            }
            while (deck[3].second.size() > 0) {
                cout << deck[3].second.front() << " " << deck[1].second.front() << endl;
                deck[3].second.erase(deck[3].second.begin());
                deck[1].second.erase(deck[1].second.begin());
            }
            while (deck[1].second.size() >= 2){
                cout << deck[1].second[0] << " " << deck[1].second[1] << endl;
                deck[1].second.erase(deck[1].second.begin());
                deck[1].second.erase(deck[1].second.begin());
            }
        } else if (mast == 'D') {
            while (deck[0].second.size() > 0) {
                cout << deck[0].second.front() << " " << deck[2].second.front() << endl;
                deck[0].second.erase(deck[0].second.begin());
                deck[2].second.erase(deck[2].second.begin());
            }
            while (deck[1].second.size() > 0) {
                cout << deck[1].second.front() << " " << deck[2].second.front() << endl;
                deck[1].second.erase(deck[1].second.begin());
                deck[2].second.erase(deck[2].second.begin());
            }
            while (deck[3].second.size() > 0) {
                cout << deck[3].second.front() << " " << deck[2].second.front() << endl;
                deck[3].second.erase(deck[3].second.begin());
                deck[2].second.erase(deck[2].second.begin());
            }
            while (deck[2].second.size() >= 2){
                cout << deck[2].second[0] << " " << deck[2].second[1] << endl;
                deck[2].second.erase(deck[2].second.begin());
                deck[2].second.erase(deck[2].second.begin());
            }
        } else if (mast == 'S') {
            while (deck[0].second.size() > 0) {
                cout << deck[0].second.front() << " " << deck[3].second.front() << endl;
                deck[0].second.erase(deck[0].second.begin());
                deck[3].second.erase(deck[3].second.begin());
            }
            while (deck[1].second.size() > 0) {
                cout << deck[1].second.front() << " " << deck[3].second.front() << endl;
                deck[1].second.erase(deck[1].second.begin());
                deck[3].second.erase(deck[3].second.begin());
            }
            while (deck[2].second.size() > 0) {
                cout << deck[2].second.front() << " " << deck[3].second.front() << endl;
                deck[2].second.erase(deck[2].second.begin());
                deck[3].second.erase(deck[3].second.begin());
            }
            while (deck[3].second.size() >= 2){
                cout << deck[3].second[0] << " " << deck[3].second[1] << endl;
                deck[3].second.erase(deck[3].second.begin());
                deck[3].second.erase(deck[3].second.begin());
            }
        }
    }
    return 0;
}