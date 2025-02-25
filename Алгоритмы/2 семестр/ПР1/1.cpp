#include <iostream>
using namespace std;

struct Node{
    int data = NULL;
    Node* firstNextNode = nullptr;
    Node* secondNextNode = nullptr;
};


bool check(Node* head, Node* point = NULL){
    if (head->firstNextNode == nullptr and head->secondNextNode == nullptr){
        return true;
    }
    if (head->firstNextNode == nullptr and head->secondNextNode != nullptr){
        return check(head->secondNextNode, head);
    }
    if (head->secondNextNode == nullptr and head->firstNextNode != nullptr){
        return check(head->firstNextNode, head);
    }
    if (head->firstNextNode != head->secondNextNode or head->firstNextNode == point or head->secondNextNode == point){
        return false;
    } else {
        return check(head->firstNextNode, head) and check(head->secondNextNode, head);
    }
}

int main(){
    Node* head = new Node();
    head->data = 0;
    Node* nextNode = new Node();
    Node* last = nextNode;
    nextNode->data = 1;
    head->firstNextNode = nextNode;
    head->secondNextNode = nextNode;
    nextNode = new Node;
    last->firstNextNode = nextNode;
    nextNode->data = 2;
    cout << check(head) << endl;
    return 0;
}