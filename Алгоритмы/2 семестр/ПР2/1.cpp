#include <iostream>
using namespace std;

struct Node {
    uint data;
    int balance = 0;
    Node* leftNode = nullptr;
    Node* rightNode = nullptr;
    Node* parent = nullptr;

    void deleteNode(){
        rightNode->deleteNode();
        leftNode->deleteNode();
        delete this;
    }
};

struct Tree {
    Node* head;

    int maxLength(Node* Node){
        if (Node == nullptr){
            return 0;
        } else {
            return max(maxLength(Node->leftNode), maxLength(Node->rightNode)) + 1; 
        }
    }

    void balanseCheck(Node* checkNode){
        if (checkNode == nullptr){
            return;
        }
        checkNode->balance = maxLength(checkNode->rightNode) - maxLength(checkNode->leftNode);
        balanseCheck(checkNode->parent);
    }
    
    void addNode(int newData){
        if (head == nullptr){
            head = new Node;
            head->data = newData;
            return;
        }
        Node* lastNode = head;
        while (true){
            if (newData >= lastNode->data){
                if (lastNode->rightNode != nullptr){
                    lastNode = lastNode->rightNode;
                    continue;
                } else {
                    lastNode->rightNode = new Node();
                    lastNode->rightNode->data = newData;
                    lastNode->rightNode->parent = lastNode;
                    break;
                }
            } else {
                if (lastNode->leftNode != nullptr){
                    lastNode = lastNode->leftNode;
                    continue;
                } else {
                    lastNode->leftNode = new Node();
                    lastNode->leftNode->data = newData;
                    lastNode->leftNode->parent = lastNode;
                    break;
                }
            }
        }
        balanseCheck(lastNode);
    }

    void deleteTree(){
        head->deleteNode();
        delete this;
    }

    void inOrderTraversal(Node* node) {
        if (node == nullptr) return;
        inOrderTraversal(node->leftNode);
        cout << node->data << "(" << node->balance << ") ";
        inOrderTraversal(node->rightNode);
    }
    
    void printInOrder() {
        inOrderTraversal(head);
        cout << endl;
    }
};

int main(){
    Tree* tree = new Tree();
    tree->addNode(1);
    tree->addNode(2);
    tree->addNode(3);
    tree->addNode(4);
    tree->addNode(5);
    tree->printInOrder();
    return 0;
}