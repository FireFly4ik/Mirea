#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* leftNode;
    Node* rightNode;
    Node* parent;
    char color = 'B';
    bool leaf = 1;
    int blackNodes = 1;

    bool checkRedBabyes(){
        bool allGood = (color == 'R' and rightNode->color == 'B' and leftNode->color == 'B' or color == 'B') ? 1 : 0;
        if (leftNode){
            allGood = allGood and leftNode->checkRedBabyes();
        }
        if (rightNode){
            allGood = allGood and rightNode->checkRedBabyes();
        }
        return allGood;
    }

    bool checkColors(){
        bool rightColor = color == 'B' or color == 'R';
        if (leftNode){
            rightColor = rightColor and  leftNode->checkColors();
        }
        if (rightNode){
            rightColor = rightColor and  rightNode->checkColors();
        }
        return rightColor;
    }

    bool checkLeaves(){
        if (leaf){
            if (rightNode or leftNode){
                return false;
            }
            if (color == 'B'){
                return true;
            } else {
                return false;
            }
        } else {
            return leftNode->checkLeaves() and rightNode->checkLeaves();
        }
    }

    int checkBlackQuantity(){
        if (leaf){
            return 1;
        }
        if (leftNode->checkBlackQuantity() != rightNode->checkBlackQuantity()){
            blackNodes = 0;
            return 0;
        } else {
            blackNodes += leftNode->checkBlackQuantity();
            return blackNodes;
        }
    }
};

struct Tree{
    Node* head;

    void addNode(int newData){
        if (!head){
            head = new Node;
            head->data = newData;
            head->leaf = false;
            createLeaves(head);
        } else {
            Node* last = head;
            while (true) {
                if (last->data <= newData){
                    if (last->rightNode->leaf){
                        last->rightNode->data = newData;
                        last->rightNode->leaf = false;
                        last->rightNode->parent = last;
                        createLeaves(last->rightNode);
                        break;
                    } else {
                        last = last->rightNode;
                        continue;
                    }
                } else {
                    if (last->leftNode->leaf){
                        last->leftNode->data = newData;
                        last->leftNode->leaf = false;
                        last->leftNode->parent = last;
                        createLeaves(last->leftNode);
                        break;
                    } else {
                        last = last->leftNode;
                        continue;
                    }
                }
            }
        }
    }

    void createLeaves(Node* node){
        if(!node->leftNode){
            node->leftNode = new Node;
        }
        if (!node->rightNode){
            node->rightNode = new Node;
        }
    }

    bool checkRules(){
        if (head->color != 'B'){
            cout << "Корень не черный" << endl;
            return false;
        }
        if (!head->checkLeaves()){
            cout << "Не каждый лист фиктивный или черный" << endl;
            return false;
        }
        if (!head->checkBlackQuantity()){
            cout << "Нет баланса черных элементов" << endl;
            return false;
        }
        if (!head->checkColors()){
            cout << "Не все цвета черные или красные" << endl;
            return false;
        }
        if (!head->checkRedBabyes()){
            cout << "Не у всех красных элементов черные дети" << endl;
            return false;
        }
        return true;
    }
};

int main(){
    Tree* tree = new Tree;
    tree->addNode(1);
    tree->addNode(2);
    tree->addNode(3);
    tree->addNode(4);
    tree->addNode(5);
    cout << tree->checkRules() << endl;
    return 0;
}