#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int val) : value(val) {}

    void deleteNodes(){
        if (left) {
            left->deleteNodes();
        }
        if (right) {
            right->deleteNodes();
        }
        delete this;
    }
};

bool checkMaxHeap(Node* node) {
    bool flag = 1;
    if (node->left) {
        if (node->left->value < node->value){
            flag = flag * checkMaxHeap(node->left);
        } else {
            return 0;
        }
    }
    if (node->right){
        if (node->right->value < node->value){
            flag = flag * checkMaxHeap(node->right);
        } else {
            return 0;
        }
    }
    return flag;
}

bool checkMinHeap(Node* node) {
    bool flag = 1;
    if (node->left) {
        if (node->left->value > node->value){
            flag = flag * checkMinHeap(node->left);
        } else {
            return 0;
        }
    }
    if (node->right){
        if (node->right->value > node->value){
            flag = flag * checkMinHeap(node->right);
        } else {
            return 0;
        }
    }
    return flag;
}

bool checkHeap(Node* node){
    return checkMaxHeap(node) + checkMinHeap(node);
}

int main() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    cout << checkHeap(root) << endl;

    root->deleteNodes();

    root = new Node(1);
    root->left = new Node(0);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    cout << checkHeap(root) << endl;

    root->deleteNodes();

    root = new Node(10);
    root->left = new Node(9);
    root->right = new Node(8);
    root->left->left = new Node(7);
    root->left->right = new Node(6);
    root->right->right = new Node(5);

    cout << checkHeap(root) << endl;

    root->deleteNodes();

    root = new Node(10);
    root->left = new Node(9);
    root->right = new Node(8);
    root->left->left = new Node(11);
    root->left->right = new Node(6);
    root->right->right = new Node(5);

    cout << checkHeap(root) << endl;

    root->deleteNodes();
    return 0;
}