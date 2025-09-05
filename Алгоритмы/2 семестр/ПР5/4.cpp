#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct Vertex;

struct Edge {
    Vertex* toVertex = nullptr;
    Edge* nextEdge = nullptr;
};

struct Vertex {
    int id;
    Edge* edge = nullptr;
    Vertex* nextVertex = nullptr;
};

class Graph {
private:
    Vertex* head = nullptr;
    int vershin, reber;
public:
    void createGraph() {
        cout << "Введите количество вершин: ";
        cin >> vershin;
        head = new Vertex;
        Vertex* last = head;
        for (int i = 1; i < vershin; i++) {
            last->nextVertex = new Vertex;
            last = last->nextVertex;
            last->id = i;
        }
        cout << "Введите количество ребер: ";
        cin >> reber;
        for (int i = 0; i < reber; i++){
            int from, to;
            cout << "Введите номера вершин из которой и в какую: ";
            cin >> from >> to;
            last = head;
            Vertex* vertexFrom = nullptr;
            Vertex* vertexTo = nullptr;
            last = head;
            for (int j = 0; j < vershin; j++){
                if (last->id == from) {
                    vertexFrom = last;
                } else if (last->id == to) {
                    vertexTo = last;
                }
                if (vertexTo != nullptr and vertexFrom != nullptr) {
                    break;
                }
                last = last->nextVertex;
            }
            if (vertexFrom->edge == nullptr) {
                vertexFrom->edge = new Edge;
                vertexFrom->edge->toVertex = vertexTo;
            } else {
                Edge* lastEdge = vertexFrom->edge;
                while (lastEdge->nextEdge != nullptr) {
                    lastEdge = lastEdge->nextEdge;
                }
                lastEdge->nextEdge = new Edge;
                lastEdge->nextEdge->toVertex = vertexTo;
            }
        }
    }

    void printSmezh(){
        Vertex* last = head;
        while (last != nullptr) {
            cout << last->id << ": ";
            Edge* lastEdge = last->edge;
            while (lastEdge != nullptr) {
                cout << lastEdge->toVertex->id << " ";
                lastEdge = lastEdge->nextEdge;
            }
            cout << endl;
            last = last->nextVertex;
        }
    }

    void DFS() {
        vector<Vertex*> ochered;
        vector<bool> visited;
        visited.resize(vershin, false);
        Vertex* last = nullptr;
        ochered.push_back(head);
        for (int i = 0; i < vershin; i++){
            last = ochered.front();
            ochered.erase(ochered.begin());
            visited[last->id] = true;
            cout << last->id << " ";
            Edge* lastEdge = last->edge;
            int vstavleno = 0;
            while (lastEdge != nullptr) {
                if (!visited[lastEdge->toVertex->id]) {
                    ochered.emplace(ochered.begin() + vstavleno, lastEdge->toVertex);
                    visited[lastEdge->toVertex->id] = true;
                    vstavleno++;
                }
                lastEdge = lastEdge->nextEdge;
            }
        }
    }
};

int main() {
    Graph graph;
    graph.createGraph();
    cout << "Список смежности: " << endl;
    graph.printSmezh();
    cout << "Поиск в глубину: " << endl;
    graph.DFS();
}