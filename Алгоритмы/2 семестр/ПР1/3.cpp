#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* previousNode = nullptr;
    Node* nextNode = nullptr;
    bool last = false;
};

void createNewNode(Node* head, int newData){
    Node* lastNode = head;
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->last = true;
    while(!lastNode->last){
        lastNode = lastNode->nextNode;
    }
    newNode->nextNode = lastNode->nextNode;
    newNode->previousNode = lastNode;
    newNode->nextNode->previousNode = newNode;
    lastNode->nextNode = newNode;
    lastNode->last = false;
}

void printSpisok(Node* head){
    Node* lastNode = head;
    while (true){
        cout << lastNode->data << " ";
        if (lastNode->last){
            break;
        } else {
            lastNode = lastNode->nextNode;
        }
    }
    cout << endl;
}

bool checkLoop(Node* head){
    Node* lastNode = head;
    while (true){
        if (lastNode->nextNode == nullptr){
            return false;
        } else if (lastNode->nextNode == head){
            return true;
        } else {
            lastNode = lastNode->nextNode;
        }
    }
}

void deleteNode(Node* head, int dataToDelete){
    Node* lastNode = head;
    while (lastNode->data != dataToDelete){
        lastNode = lastNode->nextNode;
    }
    lastNode->previousNode->last = lastNode->last;
    lastNode->nextNode->previousNode = lastNode->previousNode;
    lastNode->previousNode->nextNode = lastNode->nextNode;
    delete lastNode;
}

int main(){
    Node* head = new Node;
    head->data = 0;
    head->last = true;
    head->nextNode = head;
    head->previousNode = head;
    createNewNode(head, 1);
    createNewNode(head, 2);
    createNewNode(head, 3);
    printSpisok(head);
    cout << checkLoop(head) << endl;
    deleteNode(head, 2);
    printSpisok(head);
    deleteNode(head, 3);
    printSpisok(head);
    cout << checkLoop(head) << endl;
    return 0;
}