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
        int vershin, reber, stoimost;
        cout << "Введите количество вершин: ";
        cin >> vershin;
        matrix.resize(vershin, vector<int>(vershin, 0));
        int versina, rebro;
        cout << "Введите количество ребер: ";
        cin >> reber;
        for (int i = 0; i < reber; i++) {
            cout << "Введите номера вершин, которые соединяет ребро, и стоимость пути: ";
            cin >> versina >> rebro >> stoimost;
            matrix[versina][rebro] = stoimost;
            matrix[rebro][versina] = stoimost;
        }
    }

    void createTestGraph() {
        matrix = {{0, 197, 2160, 1070, 2230, 1040}, 
                  {197, 0, 2230, 1140, 2300, 1110},
                  {2160, 2230, 0, 1150, 520, 1200},
                  {1070, 1140, 1150, 0, 1340, 68},
                  {2230, 2300, 520, 1340, 0, 1380},
                  {1040, 1110, 1200, 68, 1380, 0}};
    }

    void prima(){
        int answer = 0;
        vector<int> path, parent;
        vector<bool> seen;
        seen.resize(matrix.size(), false);
        parent.resize(matrix.size(), -1);
        path.resize(matrix.size(), 2147483646);
        int startPos = 0;
        path[startPos] = 0;
        for (int i = 0; i < matrix.size(); i++) {
            seen[startPos] = true;
            for (int j = 0; j < matrix.size(); j++){
                if (j == startPos) {continue;}
                if (matrix[startPos][j] != 0) {
                    if (seen[j] == false and path[j] > matrix[startPos][j]) {
                        path[j] = matrix[startPos][j];
                        parent[j] = startPos;
                    }
                }
            }
            int minPath = 2147483646;
            for (int j = 0; j < matrix.size() - 1; j++){
                if (seen[j] == false) continue;
                for (int k = 0; k < matrix.size(); k++){
                    if (seen[k] == true) continue;
                    if (matrix[j][k] < minPath) {
                        minPath = matrix[j][k];
                        startPos = k;
                    }
                }
            }
        }
        for (int i = 0; i < parent.size(); i++) {
            if (parent[i] == -1) {
                continue;
            } else {
                cout << parent[i] << " " << i << endl;
            }
        }
        for (int i : path){
            answer += i;
        }
        cout << "Длина пути: " << answer << endl;
        return;
    };
};

int main() {
    Graph graph;
    int data;
    cout << "Свои данные или тестовые?(0/1): ";
    cin >> data;
    if (data) {
        graph.createTestGraph();
    } else {
        graph.createGraph();
    }
    graph.prima();
}