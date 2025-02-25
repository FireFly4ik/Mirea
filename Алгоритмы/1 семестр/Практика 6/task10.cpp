#include <iostream>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream file("forTask10.txt");
    string line;
    queue <int> q1;
    queue <int> q2;
    while (getline(file, line)){
        line.pop_back();
        if (line.length() == 2){
            q2.push(stoi(line));
        } else {
            q1.push(stoi(line));
        }
    }
    while (q1.size() > 0){
        cout << q1.front() << " ";
        q1.pop();
    }
    while (q2.size() > 0){
        cout << q2.front() << " ";
        q2.pop();
    }
    cout << endl;
}