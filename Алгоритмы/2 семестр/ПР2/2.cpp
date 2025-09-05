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
        if (!previousNode){
            Node* tempNode = rightNode ? rightNode->leftNode : nullptr;
            rightNode->previousNode = nullptr;
            *head = rightNode;
            rightNode->leftNode = this;
            this->previousNode = rightNode;
            this->rightNode = tempNode;
        } else if (previousNode->leftNode == this){
            Node* tempNode = rightNode ? rightNode->leftNode : nullptr;
            previousNode->leftNode = rightNode;
            rightNode->previousNode = previousNode;
            rightNode->leftNode = this;
            this->previousNode = rightNode;
            this->rightNode = tempNode;
        } else if (previousNode->rightNode == this) {
            Node* tempNode = rightNode ? rightNode->leftNode : nullptr;
            previousNode->rightNode = rightNode;
            rightNode->previousNode = previousNode;
            rightNode->leftNode = this;
            this->previousNode = rightNode;
            this->rightNode = tempNode;
        }
    }

    void rightTurn(){
        if (!previousNode){
            Node* tempNode = leftNode ? leftNode->rightNode : nullptr;
            leftNode->previousNode = nullptr;
            *head = leftNode;
            leftNode->rightNode = this;
            this->previousNode = leftNode;
            this->leftNode = tempNode;
        } else if (previousNode->leftNode == this){
            Node* tempNode = leftNode ? leftNode->rightNode : nullptr;
            previousNode->leftNode = leftNode;
            leftNode->previousNode = previousNode;
            leftNode->rightNode = this;
            this->previousNode = leftNode;
            this->leftNode = tempNode;
        } else if (previousNode->rightNode == this) {
            Node* tempNode = leftNode ? leftNode->rightNode : nullptr;
            previousNode->rightNode = leftNode;
            leftNode->previousNode = previousNode;
            leftNode->rightNode = this;
            this->previousNode = leftNode;
            this->leftNode = tempNode;
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
};

int main(){
    Tree* tree = new Tree();
    tree->addNode(1);
    tree->addNode(2);
    tree->addNode(3);
    tree->deleteTree();
    return 0;
}