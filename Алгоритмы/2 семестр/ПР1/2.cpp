#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* nextNode = nullptr;
};

void createNewNode(Node* head, int newData){
    Node* newNode = new Node();
    Node* last = head;
    newNode->data = newData;
    while(last->nextNode != nullptr){
        last = last->nextNode;
    }
    last->nextNode = newNode;
}

void split (Node* start, Node*& lower, Node*& higher, int point){
    Node* head = start;
    while (true) {
        if (head->data < point){
            createNewNode(lower, head->data);
        } else {
            createNewNode(higher, head->data);
        }
        if (head->nextNode != nullptr){
            head = head->nextNode;
        } else {
            break;
        }
    }
    Node* temp = lower->nextNode;
    delete lower;
    lower = temp;
    temp = higher->nextNode;
    delete higher;
    higher = temp;
}

int main(){
    Node* head = new Node();
    head->data = 0;
    createNewNode(head, 7);
    createNewNode(head, 2);
    createNewNode(head, 3);
    createNewNode(head, 6);
    createNewNode(head, 8);
    int x;
    cin >> x;
    Node* lower = new Node;
    Node* higher = new Node;
    split(head, *&lower, *&higher, x);
    cout << "bebe" << endl;
    return 0;
}