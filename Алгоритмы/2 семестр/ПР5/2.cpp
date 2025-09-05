#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Graph {
private:
    vector<vector<int>> matrix;
public:
    void createGraph() {
        int vershin, reber;
        cout << "Введите количество вершин: ";
        cin >> vershin;
        matrix.resize(vershin, vector<int>(vershin, 0));
        int versina, rebro;
        cout << "Введите количество ребер: ";
        cin >> reber;
        for (int i = 0; i < reber; i++) {
            cout << "Введите номера вершин, которые соединяет ребро: ";
            cin >> versina >> rebro;
            matrix[versina][rebro] = 1;
            matrix[rebro][versina] = 1;
        }
    }

    int checkSvyaz() {
        vector<bool> seen;
        seen.resize(matrix.size(), false);
        int answer = 0;
        BFS(&seen, 0);
        while (true) {
            int nextStart = -1;
            for (int i = 0; i < seen.size(); i++){
                if (seen[i] == false and nextStart == -1){
                    nextStart = i;
                    break;
                }
            }
            if (nextStart == -1) {
                return answer;
            }
            BFS(&seen, nextStart);
            answer ++;
        }
    }

    void BFS(vector<bool>* seen, int start) {
        (*seen)[start] = true;
        queue<int> ochered;
        ochered.push(start);
        while (ochered.size() != 0) {
            for (int i = 0; i < matrix[ochered.front()].size(); i++) {
                if (matrix[ochered.front()][i] == 1 and (*seen)[i] == false) {
                    ochered.push(i);
                    (*seen)[i] = true;
                }
            }
            ochered.pop();
        }
    }
};

int main(){
    Graph graph;
    graph.createGraph();
    cout << graph.checkSvyaz() << endl;
    return 0;
}