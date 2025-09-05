#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    Node(int data): data(data) {}

    int data;
    Node* leftNode;
    Node* rightNode;
};

struct Heap {
    void createTree(vector<int> massive){
        massive.insert(massive.begin(), 0);
        for (int i = 1; i < massive.size(); i++){
            int q = i;
            if (q == 1){
                head = new Node(massive[i]);
                continue;
            }
            vector<int> tray;
            while (q != 1){
                tray.insert(tray.begin(), q % 2);
                q /= 2;
            }
            Node* last = head;
            for (int j = 0; j < tray.size(); j++){
                if (tray[j]){
                    if (!last->rightNode) {
                        last->rightNode = new Node(massive[i]);
                        break;
                    }
                    last = last->rightNode;
                } else {
                    if (!last->leftNode) {
                        last->leftNode = new Node(massive[i]);
                        break;
                    }
                    last = last->leftNode;
                }
            }
        }
    }

    void print(Node* node, int space = 0){
        if (!node) return;
        space += 2;
        print(node->rightNode, space);
        for (int i = 2; i < space; ++i){
            cout << " ";
        }
        cout << node->data << endl;
        print(node->leftNode, space);
    }

    Node* head;
};

int main(){
    int l;
    cin >> l;
    vector<int> massive;
    for (int i = 0; i < l; i++){
        int x;
        cin >> x;
        massive.push_back(x);
    }
    sort(massive.begin(), massive.end());
    reverse(massive.begin(), massive.end());
    Heap* heap = new Heap;
    heap->createTree(massive);
    heap->print(heap->head);
    return 0;
}