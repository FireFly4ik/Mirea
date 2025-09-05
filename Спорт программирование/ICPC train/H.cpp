#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

void horse(int x, int y);
void pawn(int x, int y);
vector<vector<char>> pole;
vector<vector<int>> steps;

void horse(int x, int y) {
    if (x - 1 >= 0){
        if (y - 2 >= 0){
            if (steps[x-1][y-2] > steps[x][y] + 1) {
                if (pole[x-1][y-2] == 'p') {
                    steps[x-1][y-2] = steps[x][y] + 1;
                    pawn(x-1, y-2);
                } else if (pole[x-1][y-2] == 'h') {
                    steps[x-1][y-2] = steps[x][y] + 1;
                    horse(x-1, y-2);
                }
            }
        }
        if (y + 2 < steps.size()){
            if (steps[x-1][y+2] > steps[x][y] + 1) {
                if (pole[x-1][y+2] == 'p') {
                    steps[x-1][y+2] = steps[x][y] + 1;
                    pawn(x-1, y+2);
                } else if (pole[x-1][y+2] == 'h') {
                    steps[x-1][y+2] = steps[x][y] + 1;
                    horse(x-1, y+2);
                }
            }
        }
    }
    if (x + 1 < steps.size()){
        if (y - 2 >= 0){
            if (steps[x+1][y-2] > steps[x][y] + 1) {
                if (pole[x+1][y-2] == 'p') {
                    steps[x+1][y-2] = steps[x][y] + 1;
                    pawn(x+1, y-2);
                } else if (pole[x+1][y-2] == 'h') {
                    steps[x+1][y-2] = steps[x][y] + 1;
                    horse(x+1, y-2);
                }
            }
        }
        if (y + 2 < steps.size()){
            if (steps[x+1][y+2] > steps[x][y] + 1) {
                if (pole[x+1][y+2] == 'p') {
                    steps[x+1][y+2] = steps[x][y] + 1;
                    pawn(x+1, y+2);
                } else if (pole[x+1][y+2] == 'h') {
                    steps[x+1][y+2] = steps[x][y] + 1;
                    horse(x+1, y+2);
                }
            }
        }
    }
    if (y - 1 >= 0){
        if (x - 2 >= 0){
            if (steps[x-2][y-1] > steps[x][y] + 1) {
                if (pole[x-2][y-1] == 'p') {
                    steps[x-2][y-1] = steps[x][y] + 1;
                    pawn(x-2, y-1);
                } else if (pole[x-2][y-1] == 'h') {
                    steps[x-2][y-1] = steps[x][y] + 1;
                    horse(x-2, y-1);
                }
            }
        }
        if (x + 2 < steps.size()){
            if (steps[x+2][y-1] > steps[x][y] + 1) {
                if (pole[x+2][y-1] == 'p') {
                    steps[x+2][y-1] = steps[x][y] + 1;
                    pawn(x+2, y-1);
                } else if (pole[x+2][y-1] == 'h') {
                    steps[x+2][y-1] = steps[x][y] + 1;
                    horse(x+2, y-1);
                }
            }
        }
    }
    if (y + 1 < steps.size()){
        if (x - 2 >= 0){
            if (steps[x-2][y+1] > steps[x][y] + 1) {
                if (pole[x-2][y+1] == 'p') {
                    steps[x-2][y+1] = steps[x][y] + 1;
                    pawn(x-2, y+1);
                } else if (pole[x-2][y+1] == 'h') {
                    steps[x-2][y+1] = steps[x][y] + 1;
                    horse(x-2, y+1);
                }
            }
        }
        if (x + 2 < steps.size()){
            if (steps[x+2][y+1] > steps[x][y] + 1) {
                if (pole[x+2][y+1] == 'p') {
                    steps[x+2][y+1] = steps[x][y] + 1;
                    pawn(x+2, y+1);
                } else if (pole[x+2][y+1] == 'h') {
                    steps[x+2][y+1] = steps[x][y] + 1;
                    horse(x+2, y+1);
                }
            }
        }
    }
}

void pawn(int x, int y) {
    if (x - 1 >= 0){
        if (steps[x-1][y] > steps[x][y] + 1) {
            if (pole[x-1][y] == 'p') {
                steps[x-1][y] = steps[x][y] + 1;
                pawn(x-1, y);
            } else if (pole[x-1][y] == 'h') {
                steps[x-1][y] = steps[x][y] + 1;
                horse(x-1, y);
            }
        }
    }
    if (x + 1 < steps.size()){
        if (steps[x+1][y] > steps[x][y] + 1) {
            if (pole[x+1][y] == 'p') {
                steps[x+1][y] = steps[x][y] + 1;
                pawn(x+1, y);
            } else if (pole[x+1][y] == 'h') {
                steps[x+1][y] = steps[x][y] + 1;
                horse(x+1, y);
            }
        }
    }
    if (y - 1 >= 0){
        if (steps[x][y-1] > steps[x][y] + 1) {
            if (pole[x][y-1] == 'p') {
                steps[x][y-1] = steps[x][y] + 1;
                pawn(x, y-1);
            } else if (pole[x][y-1] == 'h') {
                steps[x][y-1] = steps[x][y] + 1;
                horse(x, y-1);
            }
        }
    }
    if (y + 1 < steps.size()){
        if (steps[x][y+1] > steps[x][y] + 1) {
            if (pole[x][y+1] == 'p') {
                steps[x][y+1] = steps[x][y] + 1;
                pawn(x, y+1);
            } else if (pole[x][y+1] == 'h') {
                steps[x][y+1] = steps[x][y] + 1;
                horse(x, y+1);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int dlina;
    cin >> dlina;
    vector<int> example;
    for (int i = 0; i < dlina; i++) {
        example.push_back(INT_MAX);
    }
    for (int i = 0; i < dlina; i++) {
        string s;
        cin >> s;
        pole.push_back({});
        for (int j = 0; j < dlina; j++) {
            pole[i].push_back(s[j]);
        }
        steps.push_back(example);
    }
    int x, y;
    cin >> x >> y;
    pair<int, int> start = {x, y};
    cin >> x >> y;
    pair<int, int> finish = {x, y};
    steps[start.first - 1][start.second- 1] = 0;
    if (pole[start.first- 1][start.second-1] == 'p') {
       pawn(start.first-1, start.second-1);
    }
    else if (pole[start.first-1][start.second-1] == 'h') {
        horse(start.first-1, start.second-1);
    }
    if (steps[finish.first - 1][finish.second - 1] == INT_MAX) {
        cout << -1 << endl;
        return 0;
    }
    cout << steps[finish.first - 1][finish.second - 1] << endl;
    return 0;
}