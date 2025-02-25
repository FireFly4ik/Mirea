#include <iostream>
using namespace std;

class Node{
public:
    Node(int newChislo){
        chislo = newChislo;
    }

    void newNode(int nextChislo){
        if (nextNodeLive == true){
            nextNode->newNode(nextChislo);
        } else {
            nextNode = new Node(nextChislo);
            nextNodeLive = true;
        }
    }

    int sumChisel(){
        if (nextNodeLive == true){
            return (nextNode->sumChisel() + chislo);
        } 
        return chislo;
    }
private:
    int chislo;
    Node *nextNode;
    bool nextNodeLive = false;
};

int main(){
    int n, x;
    cin >> n >> x;
    Node node(x);
    for (int i = 1; i < n; i++){
        cin >> x;
        node.newNode(x);
    }
    cout << node.sumChisel() << endl;
    return 0;
}