#include <iostream>
using namespace std;

struct Node{
    int data;
    int balance = 0;
    Node* leftNode = nullptr;
    Node* rightNode = nullptr;
    Node* previousNode = nullptr;
    Node** head = nullptr;

    void balancing(){
        balance = (rightNode ? rightNode->checkLength() : 0) - (leftNode ? leftNode->checkLength() : 0);
        if (balance < -1 and leftNode->leftNode){
            rightTurn();
        } else if (balance < -1 and leftNode->rightNode){
            leftNode->leftTurn();
            rightTurn();
        } else if (balance > 1 and rightNode->rightNode){
            leftTurn();
        } else if (balance > 1 and rightNode->leftNode) {
            rightNode->rightTurn();
            leftTurn();
        }
        if (previousNode){
            previousNode->balancing();
        }
    }

    void leftTurn(){
        Node* newRoot = rightNode;
        if (!newRoot) return;

        rightNode = newRoot->leftNode;
        if (rightNode) rightNode->previousNode = this;

        newRoot->leftNode = this;
        newRoot->previousNode = previousNode;
        previousNode = newRoot;

        if (newRoot->previousNode) {
            if (newRoot->previousNode->leftNode == this) {
                newRoot->previousNode->leftNode = newRoot;
            } else {
                newRoot->previousNode->rightNode = newRoot;
            }
        } else {
            *head = newRoot;
        }
    }

    void rightTurn(){
        Node* newRoot = leftNode;
        if (!newRoot) return;

        leftNode = newRoot->rightNode;
        if (leftNode) leftNode->previousNode = this;

        newRoot->rightNode = this;
        newRoot->previousNode = previousNode;
        previousNode = newRoot;

        if (newRoot->previousNode) {
            if (newRoot->previousNode->leftNode == this) {
                newRoot->previousNode->leftNode = newRoot;
            } else {
                newRoot->previousNode->rightNode = newRoot;
            }
        } else {
            *head = newRoot;
        }
    }

    int checkLength(){
        int right = 1, left = 1;
        if (rightNode){
            right += rightNode->checkLength();
        }
        if (leftNode){
            left += leftNode->checkLength();
        }
        return max(left, right);
    }

    void deleteNode(){
        if (!rightNode){
            rightNode->deleteNode();
        }
        if (!leftNode){
            leftNode->deleteNode();
        }
        delete this;
    }

};

struct Tree{
    Node* head = nullptr;

    void addNode(int newData) {
        if (!head){
            head = new Node();
            head->data = newData;
            head->head = &head;
        } else {
            Node* last = head;
            Node* previousNode = nullptr;
            while (true){
                if (newData >= last->data){
                    if (last->rightNode){
                        last = last->rightNode;
                        continue;
                    } else {
                        Node* newNode = new Node();
                        newNode->data = newData;
                        last->rightNode = newNode;
                        newNode->previousNode = last;
                        newNode->head = &head;
                        newNode->balancing();
                        break;
                    }
                } else {
                    if (last->leftNode){
                        last = last->leftNode;
                        continue;
                    } else {
                        Node* newNode = new Node();
                        newNode->data = newData;
                        last->leftNode = newNode;
                        newNode->previousNode = last;
                        newNode->head = &head;
                        newNode->balancing();
                        break;
                    }
                }
            }
        }
    }

    void deleteTree(){
        head->deleteNode();
        delete this;
    }

    void deleteNode(int dataToDelete){
        Node* last = head;
        Node* parent = nullptr;
        while (last and last->data != dataToDelete) {
            parent = last;
            last = (dataToDelete < last->data) ? last->leftNode : last->rightNode;
        }
        if (!last) return;
        if (!last->leftNode or !last->rightNode) {
            Node* replacement = last->leftNode ? last->leftNode : last->rightNode;
            if (!parent) {
                head = replacement;
            } else if (parent->leftNode == last) {
                parent->leftNode = replacement;
            } else {
                parent->rightNode = replacement;
            }
            if (replacement) replacement->previousNode = parent;
            delete last;
        } else {
            Node* successor = last->rightNode;
            while (successor->leftNode) successor = successor->leftNode;
            int successorData = successor->data;
            deleteNode(successorData);
            last->data = successorData;
        }
        if (parent) parent->balancing();
    }

    void print(Node* node, int space = 0){
        if (!node) return;
        space += 2;
        print(node->rightNode, space);
        for (int i = 2; i < space; ++i){
            cout << " ";
        }
        cout << node->data << "(" << (node->rightNode ? node->rightNode->checkLength() : 0) - (node->leftNode ? node->leftNode->checkLength() : 0) << ")" << endl;
        print(node->leftNode, space);
    }
};

int main(){
    Tree* tree = new Tree();
    tree->addNode(1);
    tree->addNode(2);
    tree->addNode(3);
    tree->addNode(4);
    tree->addNode(5);
    tree->addNode(6);
    tree->addNode(7);
    tree->addNode(8);
    tree->print(tree->head, 0);
    cout << endl;
    tree->deleteNode(2);
    tree->print(tree->head, 0);
    cout << endl;
    tree->deleteNode(1);
    tree->print(tree->head, 0);
    tree->deleteTree();
    return 0;
}