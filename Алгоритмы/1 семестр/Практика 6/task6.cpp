#include <iostream>
using namespace std;

class Node{
public:
    Node(int newChislo){
        chislo = newChislo;
        alive = true;
    }
    Node(){ }
    Node(Node*& addressNode, int newChislo){
        alive = true;
        chislo = newChislo;
        nextNodeAlive = true;
        nextNode = addressNode;
    }

    bool voidNode(){
        if (alive == false and nextNodeAlive == false){
            return true;
        } 
        return false;
    }

    int lenNode(){
        if (voidNode() == true){
            return 0;
        }
        if (nextNodeAlive == true){
            return nextNode->lenNode() + 1;
        } 
        return 1;
    }

    void print(int ind, int begin){
        if (ind == 0 and lenNode() < begin){
            cout << "Длина связанного списка меньше, чем номер элемента, с которого начинается вывод" << endl;
            return;
        }
        if (ind >= begin){
            cout << chislo << " ";
        }
        if (nextNodeAlive == true){
            nextNode->print(ind + 1, begin);
        } else { 
            cout << endl;
        }
    }

    void addNodeToEnd(int newChislo){
        if (nextNodeAlive == true){
            nextNode->addNodeToEnd(newChislo);
        } else if (alive == false){ 
            chislo = newChislo;
            alive = true;
        } else {
            nextNode = new Node(newChislo);
            nextNodeAlive = true;
        }
    }

    Node* addNodeToBegin(int newChislo, Node* addressOfNode){
        Node *newNode;
        newNode = new Node(addressOfNode, newChislo);
        return newNode;
    }

    Node* addNodeToPos(int ind, int newChislo, int score){
        if (ind == 0 and lenNode() + 1 < score){
            return this;
        } else if (ind == 0 and lenNode() + 1 == score){
            addNodeToEnd(newChislo);
        } else if (ind == 0 and score == 0) {
            return addNodeToBegin(newChislo, this);
        }
        if (ind + 1 == score){
            nextNode = nextNode->addNodeToBegin(newChislo, nextNode);
            return this;
        }
        nextNode->addNodeToPos(ind + 1, newChislo, score);
        return this;
    }

    Node* accessToNext(){
        if (nextNodeAlive){
            return nextNode;
        } else {
            cout << "Нет следующего элемента списка" << endl;
            return this;
        }
    }

private:
    int chislo = NULL;
    bool alive = false;
    bool nextNodeAlive = false;
    Node *nextNode;
};

int main(){
    Node *node;
    node = new Node;
    node->addNodeToEnd(3);
    node = node->addNodeToBegin(5, node);
    node = node->addNodeToBegin(8, node);
    node->addNodeToEnd(0);
    node->addNodeToPos(0, -3, 5);
    node = node->addNodeToPos(0, 11, 0);
    node->addNodeToPos(0, 8, 1);
    node->print(0, 0);
    cout << node->lenNode() << endl;
    return 0;
}