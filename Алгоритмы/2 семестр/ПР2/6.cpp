#include <iostream>
using namespace std;

struct Node {
    Node(int value) : data(value) {}

    int data;
    Node* leftNode = nullptr;
    Node* rightNode = nullptr;
    Node* parent = nullptr;
};

struct Tree {
    Node* head = nullptr;

    void rightTurn(Node* node) {
        Node* leftChild = node->leftNode;
        if (!leftChild) return;
        node->leftNode = leftChild->rightNode;
        if (leftChild->rightNode) leftChild->rightNode->parent = node;
        leftChild->parent = node->parent;
        if (!node->parent) {
            head = leftChild;
        } else if (node == node->parent->leftNode) {
            node->parent->leftNode = leftChild;
        } else {
            node->parent->rightNode = leftChild;
        }
        leftChild->rightNode = node;
        node->parent = leftChild;
    }

    void leftTurn(Node* node) {
        Node* rightChild = node->rightNode;
        if (!rightChild) return;
        node->rightNode = rightChild->leftNode;
        if (rightChild->leftNode) rightChild->leftNode->parent = node;
        rightChild->parent = node->parent;
        if (!node->parent) {
            head = rightChild;
        } else if (node == node->parent->leftNode) {
            node->parent->leftNode = rightChild;
        } else {
            node->parent->rightNode = rightChild;
        }
        rightChild->leftNode = node;
        node->parent = rightChild;
    }

    void splay(Node* node) {
        while (node->parent) {
            if (!node->parent->parent) {
                if (node->parent->leftNode == node){
                    rightTurn(node->parent);
                } else {
                    leftTurn(node->parent);
                }
            } else if (node->parent->leftNode == node and node->parent->parent->leftNode == node->parent) {
                rightTurn(node->parent->parent);
                rightTurn(node->parent);
            } else if (node->parent->rightNode == node and node->parent->parent->rightNode == node->parent) {
                leftTurn(node->parent->parent);
                leftTurn(node->parent);
            } else if (node->parent->leftNode == node and node->parent->parent->rightNode == node->parent) {
                rightTurn(node->parent);
                leftTurn(node->parent);
            } else {
                leftTurn(node->parent);
                rightTurn(node->parent);
            }
        }
    }

    void addNode(int newData) {
        if (!head) {
            head = new Node(newData);
            return;
        }
        Node* last = head;
        Node* parent = nullptr;
        while (last) {
            parent = last;
            if (newData < last->data) {
                last = last->leftNode;
            } else {
                last = last->rightNode;
            }
        }
        Node* newNode = new Node(newData);
        newNode->parent = parent;
        if (newData < parent->data) {
            parent->leftNode = newNode;
        } else {
            parent->rightNode = newNode;
        }
        splay(newNode);
    }

    void print(Node* node, int space = 0) {
        if (!node) return;
        space += 2;
        print(node->rightNode, space);
        for (int i = 2; i < space; ++i) cout << " ";
        cout << node->data << endl;
        print(node->leftNode, space);
    }

    void deleteNode(int data) {
        Node* temp = head;
        while (temp and temp->data != data) {
            if (data < temp->data) temp = temp->leftNode;
            else temp = temp->rightNode;
        }
        if (!temp) return;
        splay(temp);
        if (!temp->leftNode) {
            head = temp->rightNode;
            if (head) head->parent = nullptr;
        } else if (!temp->rightNode) {
            head = temp->leftNode;
            head->parent = nullptr;
        } else {
            Node* minRight = temp->rightNode;
            while (minRight->leftNode) minRight = minRight->leftNode;
            if (minRight->parent != temp) {
                minRight->parent->leftNode = minRight->rightNode;
                if (minRight->rightNode) minRight->rightNode->parent = minRight->parent;
                minRight->rightNode = temp->rightNode;
                minRight->rightNode->parent = minRight;
            }
            head = minRight;
            minRight->leftNode = temp->leftNode;
            minRight->leftNode->parent = minRight;
            head->parent = nullptr;
        }
        delete temp;
    }
};

int main() {
    Tree* tree = new Tree;
    tree->addNode(5);
    tree->addNode(2);
    tree->addNode(8);
    tree->addNode(1);
    tree->addNode(3);
    tree->print(tree->head, 0);
    tree->deleteNode(5);
    cout << endl << endl;
    tree->print(tree->head, 0);
    return 0;
}
