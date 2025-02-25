#include <iostream>
using namespace std;

struct Node{
    Node* leftNode;
    Node* rightNode;
    int left;
    int right;
};

Node* createTree(int left, int right){
    Node* head = new Node;
    head->left = left;
    head->right = right;
    if (right - left > 1){
        head->rightNode = createTree((right + left) / 2, right);
        head->leftNode = createTree(left, (right + left) / 2);
    }
    return head;
}

void printTree(Node* head){
    if (head->leftNode != nullptr){
        printTree(head->leftNode);
    }
    if (head->rightNode != nullptr){
        printTree(head->rightNode);
    }
    cout << "(" << head->left << ", " << head->right << ")" << " ";
}

int count(Node* head, int x){
    int result = (head->left <= x and head->right >= x);
    if (head->left <= x and head->rightNode != nullptr){
        result += count(head->rightNode, x);
    }
    if (head->right >= x and head->leftNode != nullptr){
        result += count(head->leftNode, x);
    }
    return result;
}  

int main(){
    Node* head = createTree(1, 6);
    printTree(head);
    cout << endl;
    cout << count(head, 6) << endl;
}