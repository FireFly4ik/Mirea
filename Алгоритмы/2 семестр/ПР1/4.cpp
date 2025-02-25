#include <iostream>
using namespace std;

struct Node{
    int data = NULL;
    bool last = false;
    Node* nextNode = nullptr;
    Node* previousNode = nullptr;
};

void addNodeToEnd(Node* head, int newData){
    if (head->last == false){
        addNodeToEnd(head->nextNode, newData);
    } else {
        Node* newNode = new Node();
        newNode->data = newData;
        head->nextNode->previousNode = newNode;
        newNode->nextNode = head->nextNode;
        newNode->last = true;
        head->last = false;
        newNode->previousNode = head;
        head->nextNode = newNode;
    }
}

void addNodeBeforeData(Node* head, int newData, int beforeData){
    if (head->nextNode->data != beforeData){
        addNodeBeforeData(head->nextNode, newData, beforeData);
    } else {
        Node* newNode = new Node();
        newNode->data = newData;
        head->nextNode->previousNode = newNode;
        newNode->nextNode = head->nextNode;
        if (head->last == true){
            head->last = false;
            newNode->last = true;
        }
        newNode->previousNode = head;
        head->nextNode = newNode;
    }
}

void deleteNodeData(Node* head, int dataToDelete){
    if (head->nextNode->data != dataToDelete){
        deleteNodeData(head->nextNode, dataToDelete);
    } else {
        Node* nodeToDelete = head->nextNode;
        nodeToDelete->nextNode->previousNode = head;
        if (head->last != true){
            head->last = nodeToDelete->last;
        }
        head->nextNode = nodeToDelete->nextNode;
        delete nodeToDelete;
    }
}

int countNodes(Node* head){
    if (!head->last){
        return 1 + countNodes(head->nextNode);
    } else {
        return 1;
    }
}

void printNodes(Node* head){
    if (!head->last){
        cout << head->data << " ";
        printNodes(head->nextNode);
    } else {
        cout << head->data << endl;
    }
}

void reversePrintNodes(Node* head){
    if (head->previousNode->last){
        reversePrintNodes(head->nextNode);
        cout << head->data << endl;
    } else if (head->last) {
        cout << head->data << " ";
    } else {
        reversePrintNodes(head->nextNode);
        cout << head->data << " ";
    }
}

// test
int main(){
    Node* head = new Node();
    head->data = 0;
    head->last = 1;
    head->previousNode = head;
    head->nextNode = head;
    addNodeToEnd(head, 1);
    addNodeToEnd(head, 2);
    addNodeBeforeData(head, 3, 2);
    addNodeBeforeData(head, 4, 0);
    deleteNodeData(head, 4);
    cout << countNodes(head) << endl;
    printNodes(head);
    reversePrintNodes(head);
    return 0;
}