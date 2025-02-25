#include <iostream>
using namespace std;

class Node{
public:
    Node(){}
    Node(int newChislo, Node* previous = nullptr){
        chislo = newChislo;
        previousNode = previous;
        alive = true;
    }
    
    void addNode(int newChislo){
        if (nextNodeAlive){
            nextNode->addNode(newChislo);
        } else if (!nextNodeAlive and !alive) {
            chislo = newChislo;
            alive = true;
        } else {
            nextNode = new Node(newChislo, this);
            nextNodeAlive = true;
        }
    }

    Node* sdvigLeft(int ind, int score){
        if (ind == score){
            return this;
        } else {
            return previousNode->sdvigLeft(ind + 1, score);
        }
    }

    Node* sdvigRight(int ind, int score){
        if (ind == score){
            return this;
        } else {
            return nextNode->sdvigRight(ind + 1, score);
        }
    }

    void cycle(Node* first){
        if (previousNode == nullptr and first != this){
            previousNode = first;
            return;
        }
        if (nextNodeAlive){
            nextNode->cycle(first);
        } else {
            nextNode = first;
            nextNodeAlive = true;
            nextNode->cycle(this);
        }
    }

private:
    int chislo;
    Node *nextNode;
    Node *previousNode;
    bool alive = false;
    bool nextNodeAlive = false;
};

int main(){
    Node *node;
    node = new Node(4);
    int length;
    cin >> length;
    for (int i = 0; i < length; i++){
        node->addNode(i);
    }
    node->cycle(node);
    node = node->sdvigLeft(0, 2);
    return 0;
}