#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first, second;
    cin >> first >> second;
    if (first == "stone"){
        if (second == "scissors" or second == "controller" or second == "knife"){
            cout << 1 << endl;
            return 0;
        } else if (second == "paper" or second == "pliers" or second == "ax"){
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    } else if (first == "paper"){
        if (second == "stone" or second == "ax" or second == "pliers"){
            cout << 1 << endl;
            return 0;
        } else if (second == "scissors" or second == "controller" or second == "knife"){
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    } else if (first == "scissors"){
        if (second == "paper" or second == "controller" or second == "pliers"){
            cout << 1 << endl;
            return 0;
        } else if (second == "stone" or second == "ax" or second == "knife"){
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    } else if (first == "pliers"){
        if (second == "knife" or second == "stone" or second == "ax"){
            cout << 1 << endl;
            return 0;
        } else if (second == "scissors" or second == "paper" or second == "controller"){
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    } else if (first == "knife"){
        if (second == "scissors" or second == "controller" or second == "paper"){
            cout << 1 << endl;
            return 0;
        } else if (second == "stone" or second == "ax" or second == "pliers"){
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    } else if (first == "controller"){
        if (second == "pliers" or second == "paper" or second == "ax"){
            cout << 1 << endl;
            return 0;
        } else if (second == "stone" or second == "scissors" or second == "knife"){
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    } else if (first == "ax"){
        if (second == "scissors" or second == "stone" or second == "knife"){
            cout << 1 << endl;
            return 0;
        } else if (second == "paper" or second == "controller" or second == "pliers"){
            cout << -1 << endl;
            return 0;
        } else {
            cout << 0 << endl;
            return 0;
        }
    }
    return 0;
}