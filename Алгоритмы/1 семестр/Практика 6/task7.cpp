#include <iostream>
using namespace std;

class Node {
public:
    Node(int newChislo){
        chislo = newChislo;
    }
    Node(int newChislo, Node* newNode){
        chislo = newChislo;
        nextNode = newNode;
        nextNodeAlive = true;
    }

    bool repetition(){
        if (nextNodeAlive == true) {
            if (nextNode->in(chislo) == true){
                return true;
            }
            return nextNode->repetition();
        } 
        return false;
    }

    void deleteRepetitions(){
        if (nextNodeAlive == true) {
            if (nextNode->in(chislo) == true){
                nextNode->deleteRepet(chislo);
            }
            return nextNode->deleteRepetitions();
        }
    }

    void deleteRepet(int repetChislo){
        if (nextNodeAlive == true) {
            if (nextNode->get(0, 0) == repetChislo){
                deleteNextNode();
            }
            if (nextNodeAlive == true){
                nextNode->deleteRepet(repetChislo);
            }
        }
    }

    void deleteNextNode(){
        Node* temporaryAddress = nextNode->addressOfNext();
        delete nextNode;
        nextNode = temporaryAddress;
        if (nextNode == nullptr){
            nextNodeAlive = false;
        }
    }

    void addNodeToEnd(int newChislo){
        if (nextNodeAlive == true){
            nextNode->addNodeToEnd(newChislo);
        } else {
            nextNode = new Node(newChislo);
            nextNodeAlive = true;
        }
    }

    int lenNode(){
        if (nextNodeAlive == true){
            return nextNode->lenNode() + 1;
        } 
        return 1;
    }

    bool in(int inChislo){
        if (chislo == inChislo){
            return true;
        }
        if (nextNodeAlive == true){
            return nextNode->in(inChislo);
        }
        return false;
    }

    int get(int ind, int score){
        if (ind == score){
            return chislo;
        }
        return nextNode->get(ind + 1, score);
    }
    
    Node* toTheEnd(){
        nextNode->addNodeToEnd(chislo);
        return nextNode;
    }

    void deleteLast(){
        if (lenNode() == 2){
            delete nextNode;
            nextNode = nullptr;
            nextNodeAlive = false;
        } else if (lenNode() > 2){
            nextNode->deleteLast();
        }
    }

    Node* toTheBegin(){
        Node *newNode;
        newNode = new Node(get(0, lenNode() - 1), this);
        deleteLast();
        return newNode;
    }

    Node* addressOfLast(){
        if (nextNodeAlive == false){
            return this;
        }
        return nextNode->addressOfLast();
    }

    Node* reverseList(Node* addressOfPrevious){
        if (nextNodeAlive == true){
            Node *newAddress = nextNode->reverseList(this);
        }
        nextNode = addressOfPrevious;
        nextNodeAlive = ((addressOfPrevious != nullptr) ? true : false);
        return this;
    }

    Node* addressOfNext(){
        return nextNode;
    }

private:
    int chislo;
    Node *nextNode;
    bool nextNodeAlive;
};

bool equality(Node* node1, Node* node2){
    if (node1->lenNode() == node2->lenNode()){
        for (int i = 0; i < node1->lenNode(); i++){
            if (node1->get(0, i) != node2->get(0, i)){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool contains(Node* node1, Node* node2){
    for (int i = 0; i < node2->lenNode(); i++){
        if (node1->in(node2->get(0, i)) == false){
            return false;
        }
    }
    return true;
}

void addListToEnd(Node* node1, Node* node2){
    for (int i = 0; i < node2->lenNode(); i++){
        node1->addNodeToEnd(node2->get(0, i));
    }
}

Node* reverseList(Node* node){
    Node* addressOfLast = node->addressOfLast();
    node->reverseList(nullptr);
    return addressOfLast;
}

int main(){
    Node *node1;
    Node *node2;
    node1 = new Node(1);
    node2 = new Node(1);
    node1->addNodeToEnd(2);
    node2->addNodeToEnd(2);
    node1->addNodeToEnd(3);
    node1 = node1->toTheBegin();
    node1 = reverseList(node1);
    addListToEnd(node1, node2);
    node1->deleteRepetitions();
    cout << node1->repetition() << endl;
    return 0;
}