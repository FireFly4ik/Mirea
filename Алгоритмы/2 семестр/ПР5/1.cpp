#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class Graph {
private:
    vector<vector<int>> matrix;
    bool smezh;
public:
    void createGraph() {
        bool smezhnosti;
        int vershin, reber;
        cout << "Введите 1/0 если, граф должен иметь матрицу смежности: ";
        cin >> smezhnosti;
        cout << "Введите количество вершин: ";
        cin >> vershin;
        if (smezhnosti) {
            smezh = true;
            matrix.resize(vershin, vector<int>(vershin, 0));
            int versina, rebro;
            for (int i = 0; i < vershin; i++) {
                cout << "Введите " << i + 1 << " строку матрицы смежности (элементы 0/1 через пробел): ";
                for (int j = 0; j < vershin; j++) {
                    int x;
                    cin >> x;
                    matrix[i][j] = x;
                }
            }
        } else {
            cout << "Введите количество ребер: ";
            cin >> reber;
            matrix.resize(vershin, vector<int>(reber, 0));
            int napravlenie;
            for (int i = 0; i < vershin; i++) {
                for (int j = 0; j < reber; j ++) {
                    cout << "Введите " << i + 1 << " строку матрицы инцидености (элементы -1/0/1 через пробел): ";
                    cin >> napravlenie;
                    matrix[i][j] = napravlenie;
                }
            }
        }
    }

    void BFS() {
        int start;
        cout << "Введите с какой вершины начинать обход: ";
        cin >> start;
        vector<bool> seen;
        seen.resize(matrix.size(), false);
        seen[start] = true;
        queue<int> ochered;
        ochered.push(start);
        if (smezh) {
            while (ochered.size() != 0) {
                cout << ochered.front() << " ";
                for (int i = 0; i < matrix[ochered.front()].size(); i++) {
                    if (matrix[ochered.front()][i] == 1 and seen[i] == false) {
                        ochered.push(i);
                        seen[i] = true;
                    }
                }
                ochered.pop();
            }
        } else {
            while (ochered.size() != 0) {
                cout << ochered.front() << " ";
                vector<pair<int, int>> rebra;
                for (int i = 0; i < matrix[ochered.front()].size(); i++) {
                    if (matrix[ochered.front()][i] == 1) {
                        rebra.push_back({i, ochered.front()});
                    }
                }
                while (rebra.size() != 0) {
                    for (int i = 0; i < matrix.size(); i++ ){
                        if (matrix[i][rebra[0].first] == 1 and i != rebra[0].second and seen[i] == false){
                            ochered.push(i);
                            seen[i] = true;
                            break;
                        }
                    }
                    rebra.erase(rebra.begin());
                }
                ochered.pop();
            }
        }
        cout << endl;
    }
};

int main() {
    Graph graph;
    graph.createGraph();
    graph.BFS();
    return 0;
}