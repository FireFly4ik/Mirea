#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* leftNode;
    Node* rightNode;
    Node* parent;
    Node** headOfTree;
    char color = 'B';
    bool leaf = 1;
    int blackNodes = 1;

    bool checkAllBlackWithoutDad() {
        if (parent->color == 'R' and (parent->leftNode == this ? parent->rightNode : parent->leftNode)->color == 'B' and (parent->leftNode == this ? parent->rightNode : parent->leftNode)->leftNode->color == 'B' and (parent->leftNode == this ? parent->rightNode : parent->leftNode)->rightNode->color == 'B'){
            return true;
        } else {
            return false;
        }
    }

    void leftTurn(){
        Node* newRoot = rightNode;
        if (!newRoot) return;

        rightNode = newRoot->leftNode;
        if (rightNode) rightNode->parent = this;

        newRoot->leftNode = this;
        newRoot->parent = parent;
        parent = newRoot;

        if (newRoot->parent) {
            if (newRoot->parent->leftNode == this) {
                newRoot->parent->leftNode = newRoot;
            } else {
                newRoot->parent->rightNode = newRoot;
            }
        } else {
            *headOfTree = newRoot;
        }
    }

    void rightTurn(){
        Node* newRoot = leftNode;
        if (!newRoot) return;

        leftNode = newRoot->rightNode;
        if (leftNode) leftNode->parent = this;

        newRoot->rightNode = this;
        newRoot->parent = parent;
        parent = newRoot;

        if (newRoot->parent) {
            if (newRoot->parent->leftNode == this) {
                newRoot->parent->leftNode = newRoot;
            } else {
                newRoot->parent->rightNode = newRoot;
            }
        } else {
            *headOfTree = newRoot;
        }
    }

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

    pair<bool, bool> checkCorneredBroSonRed(){
        bool isLeft = this->parent->leftNode == this;
        if (isLeft){
            if (parent->rightNode->color == 'B' and parent->rightNode->leftNode->color == 'R'){
                return pair<bool,bool> {1, 1};
            } else {
                return pair<bool,bool> {0, 1};
            }
        } else {
            if (parent->leftNode->color == 'B' and parent->leftNode->rightNode->color == 'R'){
                return pair<bool,bool> {1, 0};
            } else {
                return pair<bool,bool> {0, 0};
            }
        }
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
        if (!this){
            return 0;
        }
        if (leaf){
            return 1;
        }
        if (leftNode->checkBlackQuantity() != rightNode->checkBlackQuantity()){
            blackNodes = 0;
            return 0;
        } else {
            blackNodes = leftNode->checkBlackQuantity() + (color == 'B');
            return blackNodes;
        }
    }

    pair<bool,bool> checkLinedBroSonRed() {
        bool isLeft = this->parent->leftNode == this;
        if (isLeft){
            if (parent->rightNode->color == 'B' and parent->rightNode->rightNode->color == 'R'){
                return pair<bool,bool> {1, 1};
            } else {
                return pair<bool,bool> {0, 1};
            }
        } else {
            if (parent->leftNode->color == 'B' and parent->leftNode->leftNode->color == 'R'){
                return pair<bool,bool> {1, 0};
            } else {
                return pair<bool,bool> {0, 0};
            }
        }
    }

    void swapColor(bool nextNodes){
        if (leaf){return;}
        color = (color == 'R' ? 'B' : 'R');
        if (nextNodes){
            if (leftNode) {leftNode->swapColor(1);}
            if (rightNode) {rightNode->swapColor(1);}
        }
    }

    bool checkUncleColor(){
        if (!parent or !parent->parent){
            return 0;
        }
        if (parent->parent->rightNode == parent){
            return parent->parent->leftNode->color == 'R';
        } else {
            return parent->parent->rightNode->color == 'R';
        }
    }

    void uncleRed(){
        parent->color = (color == 'R' ? 'B' : 'R');
        if (parent->parent != *headOfTree) {parent->parent->color = (parent->parent->color == 'R' ? 'B' : 'R');}
        if (parent->parent->rightNode == parent){
            parent->parent->leftNode->color = (color == 'R' ? 'B' : 'R');
            parent->parent->rightNode->color = 'B';
        } else {
            parent->parent->rightNode->color = (color == 'R' ? 'B' : 'R');
            parent->parent->rightNode->color = 'L';
        }
    }

    bool checkLineUncleBlack(){
        if (checkUncleColor() or !parent or !parent->parent){
            return 0;
        }
        if (parent->leftNode == this){
            if (parent->parent->leftNode == parent){
                return 1;
            } else {
                return 0;
            }
        } else {
            if (parent->parent->rightNode == parent){
                return 1;
            } else {
                return 0;
            }
        }
    }

    void lineUncleBlack(){
        parent->swapColor(0);
        parent->parent->swapColor(0);
        Node* tempParentParent = parent->parent;
        if (this == parent->leftNode){
            delete parent->rightNode;
            parent->parent->rightTurn();
            tempParentParent->leftNode = new Node();
        } else {
            delete parent->leftNode;
            parent->parent->leftTurn();
            tempParentParent->rightNode = new Node();
        }
    }

    bool checkCornerUncleBlack(){
        if (checkUncleColor() or !parent or !parent->parent){
            return 0;
        }
        if (parent->color == 'B'){return 0;}
        if (parent->rightNode == this){
            if (parent->parent->leftNode == parent){
                return 1;
            } else {
                return 0;
            }
        } else {
            if (parent->parent->rightNode == parent){
                return 1;
            } else {
                return 0;
            }
        }
    }

    void cornerUncleBlack(){
        delete rightNode;
        delete leftNode;
        swapColor(0);
        parent->parent->swapColor(0);
        if (parent->rightNode == this){
            rightNode = parent->parent;
            leftNode = parent;
            rightNode->leftNode = new Node();
            leftNode->parent = this;
            parent = rightNode->parent;
            if (!rightNode->parent) {
                *headOfTree = this;
            } else {
                if (parent->rightNode == rightNode){
                    parent->rightNode = this;
                } else {
                    parent->leftNode = this;
                }
            }
            rightNode->parent = this;
            leftNode->color = 'B';
            rightNode->rightNode->color = 'R';
        } else {
            leftNode = parent->parent;
            rightNode = parent;
            leftNode->rightNode = new Node();
            rightNode->parent = this;
            parent = leftNode->parent;
            if (!leftNode->parent) {
                *headOfTree = this;
            } else {
                if (parent->leftNode == leftNode){
                    parent->leftNode = this;
                } else {
                    parent->rightNode = this;
                }
            }
            leftNode->parent = this;
            rightNode->color = 'B';
            leftNode->leftNode->color = 'R';
        }
    }

    pair<bool, bool> onlyBroRed(){
        bool isLeft = parent->leftNode == this;
        if (isLeft){
            if (parent->rightNode->color == 'R' and parent->rightNode->leftNode->color == 'B' and parent->rightNode->rightNode->color == 'B'){
                return pair<bool, bool> {1, 1};
            } else {
                return pair<bool, bool> {0, 1};
            }
        } else {
            if (parent->leftNode->color == 'R' and parent->leftNode->leftNode->color == 'B' and parent->leftNode->rightNode->color == 'B'){
                return pair<bool, bool> {1, 0};
            } else {
                return pair<bool, bool> {0, 0};
            }
        }
    }

    pair<bool, bool> checkAllBlack() {
        bool isLeft = parent->leftNode == this;
        if (isLeft){
            if (parent->rightNode->color == 'B' and parent->rightNode->leftNode->color == 'B' and parent->rightNode->rightNode->color == 'B'){
                return pair<bool, bool> {1, 1};
            } else {
                return pair<bool, bool> {0, 1};
            }
        } else {
            if (parent->leftNode->color == 'B' and parent->leftNode->leftNode->color == 'B' and parent->leftNode->rightNode->color == 'B'){
                return pair<bool, bool> {1, 0};
            } else {
                return pair<bool, bool> {0, 0};
            }
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
            head->headOfTree = &head;
            head->color = 'B';
            createLeaves(head);
        } else {
            Node* last = head;
            while (true) {
                if (last->data <= newData){
                    if (last->rightNode->leaf){
                        last->rightNode->data = newData;
                        last->rightNode->leaf = false;
                        last->rightNode->color = 'R';
                        last->rightNode->parent = last;
                        last->rightNode->headOfTree = &head;
                        createLeaves(last->rightNode);
                        if (last->rightNode->checkUncleColor()){
                            last->rightNode->uncleRed();
                            cout << checkRules() << endl;
                            break;
                        }
                        if (last->rightNode->checkLineUncleBlack()){
                            last->rightNode->lineUncleBlack();
                            createLeaves(last);
                            cout << checkRules() << endl;
                            break;
                        }
                        if (last->rightNode->checkCornerUncleBlack()){
                            last->rightNode->cornerUncleBlack();
                            createLeaves(last);
                            cout << checkRules() << endl;
                            break;
                        }
                        cout << checkRules() << endl;
                        break;
                    } else {
                        last = last->rightNode;
                        continue;
                    }
                } else {
                    if (last->leftNode->leaf){
                        last->leftNode->data = newData;
                        last->leftNode->leaf = false;
                        last->leftNode->color = 'R';
                        last->leftNode->parent = last;
                        last->leftNode->headOfTree = &head;
                        createLeaves(last->leftNode);
                        if (last->leftNode->checkUncleColor()){
                            last->leftNode->uncleRed();
                            cout << checkRules() << endl;
                            break;
                        }
                        if (last->leftNode->checkLineUncleBlack()){
                            last->leftNode->lineUncleBlack();
                            createLeaves(last);
                            cout << checkRules() << endl;
                            break;
                        }
                        if (last->leftNode->checkCornerUncleBlack()){
                            last->leftNode->cornerUncleBlack();
                            createLeaves(last);
                            cout << checkRules() << endl;
                            break;
                        }
                        cout << checkRules() << endl;
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

    void deleteNode(int dataToDelete){
        if (head->data == dataToDelete and !head->leftNode and !head->rightNode){
            delete head;
            return;
        }
        Node* last = head;
        while (true){
            if (last->data < dataToDelete){
                if (last->rightNode){
                    last = last->rightNode;
                    continue;
                } else {
                    cout << "Нода нет в дереве" << endl;
                    break;
                }
            } else if (last->data > dataToDelete){
                if (last->leftNode){
                    last = last->leftNode;
                    continue;
                } else {
                    cout << "Нода нет в дереве" << endl;
                    break;
                }
            } else {
                bool allGood = 0;
                if (last->color == 'R'){
                    allGood = 1;
                }
                if (last->leftNode->leaf and last->rightNode->leaf){
                    delete last->leftNode;
                    last->rightNode->parent = last->parent;
                    Node* temp = last->rightNode;
                    (last->parent->leftNode == last ? last->parent->leftNode : last->parent->rightNode) = last->rightNode;
                    delete last;
                    last = temp;
                } else if (!last->leftNode->leaf){
                    Node* maxNode = last->leftNode;
                    while (!maxNode->rightNode->leaf){
                        maxNode = maxNode->rightNode;
                    }
                    if (maxNode->color == 'R'){
                        if (!allGood){maxNode->color = 'B';}
                        allGood = 1;
                    }
                    if (maxNode != last->leftNode){
                        if (!maxNode->leftNode->leaf){
                            maxNode->leftNode->parent = maxNode->parent;
                            maxNode->parent->rightNode = maxNode->leftNode;
                        } else {
                            maxNode->parent->rightNode = new Node;
                            delete maxNode->leftNode;
                        }
                        delete maxNode->rightNode;
                        maxNode->parent = last->parent;
                        (last->parent->leftNode == last ? last->parent->leftNode : last->parent->rightNode) = maxNode;
                        maxNode->rightNode = last->rightNode;
                        maxNode->rightNode->parent = maxNode;
                        maxNode->leftNode = last->leftNode;
                        maxNode->leftNode->parent = maxNode;
                        delete last;
                        last = maxNode;
                    } else {
                        maxNode->parent = last->parent;
                        (last->parent->leftNode == last ? last->parent->leftNode : last->parent->rightNode) = maxNode;
                        maxNode->rightNode = last->rightNode;
                        maxNode->rightNode->parent = maxNode;
                        delete last;
                        last = maxNode;
                    }
                } else {
                    Node* minNode = last->rightNode;
                    while (!minNode->leftNode->leaf){
                        minNode = minNode->leftNode;
                    }
                    if (minNode->color == 'R'){
                        if (!allGood){minNode->color = 'B';}
                        allGood = 1;
                    }
                    if (minNode != last->rightNode){
                        if (!minNode->rightNode->leaf){
                            minNode->rightNode->parent = minNode->parent;
                            minNode->parent->leftNode = minNode->rightNode;
                        } else {
                            minNode->parent->leftNode = new Node;
                            delete minNode->rightNode;
                        }
                        delete minNode->leftNode;
                        minNode->parent = last->parent;
                        (last->parent->rightNode == last ? last->parent->rightNode : last->parent->leftNode) = minNode;
                        minNode->leftNode = last->leftNode;
                        minNode->leftNode->parent = minNode;
                        minNode->rightNode = last->rightNode;
                        minNode->rightNode->parent = minNode;
                        delete last;
                        last = minNode;
                    } else {
                        minNode->parent = last->parent;
                        (last->parent->leftNode == last ? last->parent->leftNode : last->parent->rightNode) = minNode;
                        minNode->leftNode = last->leftNode;
                        minNode->leftNode->parent = minNode;
                        delete last;
                        last = minNode;
                    }
                }
                if (!allGood){
                    if (last->checkAllBlackWithoutDad()){
                        last->parent->color = 'B';
                        (last->parent->rightNode == last ? last->parent->leftNode : last->parent->rightNode)->color = 'R';
                        cout << checkRules() << endl;
                        return;
                    } else if (pair<bool, bool> answ = last->checkLinedBroSonRed(); answ.first == 1){
                        if (answ.second){
                            swap(last->parent->color, last->parent->rightNode->color);
                            last->parent->rightNode->rightNode->color = 'B';
                            last->parent->leftTurn();
                            cout << checkRules() << endl;
                            return;
                        } else {
                            swap(last->parent->color, last->parent->leftNode->color);
                            last->parent->leftNode->leftNode->color = 'B';
                            last->parent->rightTurn();
                            cout << checkRules() << endl;
                            return;
                        }
                    } else if (pair<bool, bool> answ = last->checkCorneredBroSonRed(); answ.first == 1){
                        if (answ.second){
                            last->parent->rightNode->rightTurn();
                            swap(last->parent->color, last->parent->rightNode->color);
                            last->parent->rightNode->rightNode->color = 'B';
                            last->parent->leftTurn();
                            cout << checkRules() << endl;
                            return;
                        } else {
                            last->parent->leftNode->leftTurn();
                            swap(last->parent->color, last->parent->leftNode->color);
                            last->parent->leftNode->leftNode->color = 'B';
                            last->parent->rightTurn();
                            cout << checkRules() << endl;
                            return;
                        }
                    } else if (pair<bool, bool> answ = last->onlyBroRed(); answ.first == 1){
                        if (answ.second){
                            swap(last->parent->color, last->parent->rightNode->color);
                            last->parent->leftTurn();

                            if (last->parent->rightNode->checkBlackQuantity() > last->checkBlackQuantity()){
                                last->parent->leftTurn();
                                if (last->parent->rightNode->color == 'R' and last->parent->color == 'R'){
                                    last->parent->color = 'B';
                                    last->parent->parent->color = 'R';
                                    last->parent->parent->rightNode->color = 'B';
                                }
                            }
                            cout << checkRules() << endl;
                            return;
                        } else {
                            swap(last->parent->color, last->parent->leftNode->color);
                            last->parent->rightTurn();
                            if (last->parent->leftNode->checkBlackQuantity() > last->checkBlackQuantity()){
                                last->parent->rightTurn();
                                if (last->parent->leftNode->color == 'R' and last->parent->color == 'R'){
                                    last->parent->color = 'B';
                                    last->parent->parent->color = 'R';
                                    last->parent->parent->leftNode->color = 'B';
                                }
                            }
                            cout << checkRules() << endl;
                            return;
                        }
                    } else if (pair<bool, bool> answ = last->checkAllBlack(); answ.first == 1) {
                        if (answ.second){
                            last->parent->rightNode->color = 'R';
                            cout << checkRules() << endl;
                            return;
                        } else {
                            last->parent->leftNode->color = 'R';
                            cout << checkRules() << endl;
                            return;
                        }
                    } else {
                        cout << checkRules() << endl;
                        return;
                    }
                } else {
                    cout << checkRules() << endl;
                    return;
                }
            }
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

    void print(Node* node, int space = 0){
        if (!node) return;
        space += 2;
        print(node->rightNode, space);
        for (int i = 2; i < space; ++i){
            cout << " ";
        }
        cout << node->data << "(" << (node->color) << ")" << endl;
        print(node->leftNode, space);
    }
};

int main(){
    Tree* tree = new Tree;
    tree->addNode(1);
    tree->addNode(2);
    tree->addNode(3);
    tree->addNode(4);
    tree->addNode(5);
    tree->print(tree->head, 0);
    return 0;
}