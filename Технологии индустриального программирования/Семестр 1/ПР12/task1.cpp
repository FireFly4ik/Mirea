#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
int files = 0;
vector<vector<int>> tray;
bool returnable = false;
vector<vector<string>> lab;

bool in (vector<int> koords){
    for (int i = 0; i < tray.size(); i++){
        if (tray[i] == koords){
            return true;
        }
    }
    return false;
}

void show_vector(vector<vector<string>>&a)
{
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < a[i].size(); j++){
            cout<<a[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void check(vector<int> koords){
    vector<vector<int>> nextKoords;
    if (koords[0] + 1 < n){
        if (lab[koords[0] + 1][koords[1]] == "0" and in({koords[0] + 1, koords[1]}) == false){
            tray.push_back({koords[0] + 1, koords[1]});
            nextKoords.push_back({koords[0] + 1, koords[1]});
        } else if (lab[koords[0] + 1][koords[1]] == "s" and in({koords[0] + 1, koords[1]}) == false){
            returnable = true;
            tray.push_back({koords[0] + 1, koords[1]});
            nextKoords.push_back({koords[0] + 1, koords[1]});
        } else if (lab[koords[0] + 1][koords[1]] == "p" and in({koords[0] + 1, koords[1]}) == false){
            files++;
            tray.push_back({koords[0] + 1, koords[1]});
            nextKoords.push_back({koords[0] + 1, koords[1]});
        }
    }
    if (koords[0] - 1 > -1){
        if (lab[koords[0] - 1][koords[1]] == "0" and in({koords[0] - 1, koords[1]}) == false){
            tray.push_back({koords[0] - 1, koords[1]});
            nextKoords.push_back({koords[0] - 1, koords[1]});
        } else if (lab[koords[0] - 1][koords[1]] == "s" and in({koords[0] - 1, koords[1]}) == false){
            returnable = true;
            tray.push_back({koords[0] - 1, koords[1]});
            nextKoords.push_back({koords[0] - 1, koords[1]});
        } else if (lab[koords[0] - 1][koords[1]] == "p" and in({koords[0] - 1, koords[1]}) == false){
            files++;
            tray.push_back({koords[0] - 1, koords[1]});
            nextKoords.push_back({koords[0] - 1, koords[1]});
        }
    }
    if (koords[1] + 1 < m){
        if (lab[koords[0]][koords[1] + 1] == "0" and in({koords[0], koords[1] + 1}) == false){
            tray.push_back({koords[0], koords[1] + 1});
            nextKoords.push_back({koords[0], koords[1] + 1});
        } else if (lab[koords[0]][koords[1] + 1] == "s" and in({koords[0], koords[1] + 1}) == false){
            returnable = true;
            tray.push_back({koords[0], koords[1] + 1});
            nextKoords.push_back({koords[0], koords[1] + 1});
        } else if (lab[koords[0]][koords[1] + 1] == "p" and in({koords[0], koords[1] + 1}) == false){
            files++;
            tray.push_back({koords[0], koords[1] + 1});
            nextKoords.push_back({koords[0], koords[1] + 1});
        }
    }
    if (koords[1] - 1 > -1){
        if (lab[koords[0]][koords[1] - 1] == "0" and in({koords[0], koords[1] - 1}) == false){
            tray.push_back({koords[0], koords[1] - 1});
            nextKoords.push_back({koords[0], koords[1] - 1});
        } else if (lab[koords[0]][koords[1] - 1] == "s" and in({koords[0], koords[1] - 1}) == false){
            returnable = true;
            tray.push_back({koords[0], koords[1] - 1});
            nextKoords.push_back({koords[0], koords[1] - 1});
        } else if (lab[koords[0]][koords[1] - 1] == "p" and in({koords[0], koords[1] - 1}) == false){
            files++;
            tray.push_back({koords[0], koords[1] - 1});
            nextKoords.push_back({koords[0], koords[1] - 1});
        }
    }
    if (nextKoords.size() != 0){
        for (int i = 0; i < nextKoords.size(); i++){
            check(nextKoords[i]);
        }
    }
}

int main(){
    cin >> n >> m;
    vector<int> finish;
    for (int i = 0; i < n; i++){
        vector<string> bufer;
        for (int j = 0; j < m; j++){
            string kletka;
            cin >> kletka;
            if (kletka == "e"){
                finish.push_back(i);
                finish.push_back(j);
            }
            bufer.push_back(kletka);
        }
        lab.push_back(bufer);
    }
    tray.push_back(finish);
    check(finish);
    if (returnable){
        cout << files << endl;
    } else {
        cout<< "P.Diddy застрял в особняке с pdf-файлами" << endl;
    }
    return 0;
}