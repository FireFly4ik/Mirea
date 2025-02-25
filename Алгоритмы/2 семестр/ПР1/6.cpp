#include <random>
#include <iostream>
#include <string>
using namespace std;

class Node{
public:
    Node(int newValue){
        value = newValue;
    }
    
    bool search(int valueToSearch){
        if (value == valueToSearch){
            return true;
        } else {
            if (rightNode == nullptr and leftNode == nullptr){
                return false;
            }
            if (leftNode != nullptr and valueToSearch < value){
                return leftNode->search(valueToSearch);
            }
            if (rightNode != nullptr and valueToSearch > value){
                return rightNode->search(valueToSearch);
            }
        }
    }

    int depth(){
        if (rightNode == nullptr and leftNode == nullptr){
            return 1;
        } else {
            if (rightNode != nullptr and leftNode != nullptr){
                return max(rightNode->depth(), leftNode->depth()) + 1;
            }
            if (leftNode != nullptr){
                return leftNode->depth() + 1;
            }
            if (rightNode != nullptr){
                return rightNode->depth() + 1;
            }
        }
    }

    void addNode(int newValue){
        if (newValue < value){
            if (leftNode == nullptr){
                leftNode = new Node(newValue);
            } else {
                leftNode->addNode(newValue);
            }
        } else if (newValue > value){
            if (rightNode == nullptr){
                rightNode = new Node(newValue);
            } else {
                rightNode->addNode(newValue);
            }
        } else {
            count ++;
        }
    }
    
    void deleteNode(){
        if (rightNode != nullptr){
            rightNode->deleteNode();
        }
        if (leftNode != nullptr){
            leftNode->deleteNode();
        }
        delete(this);
    }

    void deleteValue(int valueToDelete){
        if (value == valueToDelete){
            if (leftNode == nullptr and rightNode == nullptr){
                delete(this);
            } else if (leftNode != nullptr){
                if (leftNode->haveRight()){
                    count = leftNode->returnMaxCount();
                    value = leftNode->returnMax();
                } else {
                    value = leftNode->getValue();
                    count = leftNode->getCount();
                    leftNode = leftNode->getLeft();
                }
            } else if (rightNode != nullptr){
                if (rightNode->haveLeft()){
                    count = rightNode->returnMinCount();
                    value = rightNode->returnMin();
                } else {
                    value = rightNode->getValue();
                    count = rightNode->getCount();
                    rightNode = rightNode->getRight();
                }
            }
        } else {
            if (valueToDelete < value){
                if (leftNode->getValue() == valueToDelete and !leftNode->haveLeft() and !leftNode->haveRight()){
                    leftNode = nullptr;
                    return;
                }
                leftNode->deleteValue(valueToDelete);
            } else {
                if (rightNode->getValue() == valueToDelete and !rightNode->haveLeft() and !rightNode->haveRight()){
                    rightNode = nullptr;
                    return;
                }
                rightNode->deleteValue(valueToDelete);
            }
        }
    }

    bool elementAlive(vector<int> path){
        if (path.size() == 0){
            return true;
        }
        if (path[0] == 1){
            if (rightNode != nullptr){
                vector<int> pathToThrow = path;
                pathToThrow.erase(pathToThrow.begin());
                return rightNode->elementAlive(pathToThrow);
            } else {
                return false;
            }
        } else {
            if (leftNode != nullptr){
                vector<int> pathToThrow = path;
                pathToThrow.erase(pathToThrow.begin());
                return leftNode->elementAlive(pathToThrow);
            } else {
                return false;
            }
        }
    }

    int getElement(vector<int> path){
        if (path.size() == 0){
            return value;
        }
        if (path[0] == 1){
            vector<int> pathToThrow = path;
            pathToThrow.erase(pathToThrow.begin());
            return rightNode->getElement(pathToThrow);
        } else {
            vector<int> pathToThrow = path;
            pathToThrow.erase(pathToThrow.begin());
            return leftNode->getElement(pathToThrow);
        }
    } 

    int getValue(){
        return value;
    }
private:
    Node *leftNode = nullptr;
    Node *rightNode = nullptr;
    int value;
    int count = 1;

    int getCount(){
        return count;
    }

    bool haveRight(){
        return rightNode != nullptr;
    }

    bool haveLeft(){
        return leftNode != nullptr;
    }

    Node* getLeft(){
        return leftNode;
    }

    Node* getRight(){
        return rightNode;
    }

    int returnMax(){
        if (rightNode == nullptr){
            return value;
        } else {
            int valueToReturn = rightNode->returnMax();
            if (rightNode->getValue() == valueToReturn){
                rightNode = nullptr;
            }
            return valueToReturn;
        }
    }

    int returnMaxCount(){
        if (rightNode == nullptr){
            return count;
        } else {
            int countToReturn = rightNode->returnMaxCount();
            return countToReturn;
        }
    }

    int returnMin(){
        if (leftNode == nullptr){
            return value;
        } else {
            int valueToReturn = leftNode->returnMin();
            if (leftNode->getValue() == valueToReturn){
                leftNode = nullptr;
            }
            return valueToReturn;
        }
    }

    int returnMinCount(){
        if (leftNode == nullptr){
            return count;
        } else {
            int countToReturn = leftNode->returnMinCount();
            return countToReturn;
        }
    }
};

class Tree{
public:
    void addNode(int newValue){
        if (root == nullptr){
            root = new Node(newValue);
        } else {
            root->addNode(newValue);
        }
    }

    int depthTree(){
        if (root != nullptr){
            return root->depth();
        } else {
            cout << "Дерево мертво" << endl;
            return 0;
        }
    }

    void searchNode(int value){
        if (root != nullptr){
            if (root->search(value)){
                cout << "Значение есть в дереве" << endl;
            } else {
                cout << "Значения нет в дереве" << endl;
            }
        } else {
            cout << "Дерево мертво" << endl;
        }
    }

    void deleteValue(int value){
        if (root->search(value)){
            root->deleteValue(value);
        } else {
            cout << "Значения нет в дереве" << endl;
        }
    }

    void printTree(){
        if (depthTree() == 0){
            cout << "Дерево мертво" << endl;
            return;
        }
        int dlinaStroki = pow(2.0, double(depthTree())) * 3 + 1;
        int kolvoElementov = pow(2.0, double(depthTree() + 1)) - 1;
        vector<string> elements;
        for (int i = 1; i < kolvoElementov + 1; i++){
            if (root->elementAlive(path(i))){
                string element = to_string(root->getElement(path(i)));
                if (element.length() == 1){
                    element.insert(element.begin(), ' ');
                }
                elements.push_back(element);
            } else {
                elements.push_back("  ");
            }
        }
        for (int i = 0; i < depthTree(); i++){
            for (int j = pow(2.0, i) - 1; j < pow(2.0, i + 1) - 1; j++){
                for (int k = 0; k < (dlinaStroki - int(pow(2.0, i))) / (int(pow(2.0, i)) + 1); k++){
                    cout << " ";
                }
                cout << elements[j];
            }
            for (int k = 0; k < (dlinaStroki - int(pow(2.0, i))) / (int(pow(2.0, i)) + 1) + dlinaStroki % 2; k++){
                cout << " ";
            }
            cout << endl;
            for (int j = pow(2.0, i) - 1; j < pow(2.0, i + 1) - 1; j++){
                for (int k = 0; k < (dlinaStroki - int(pow(2.0, i))) / (int(pow(2.0, i)) + 1); k++){
                    cout << " ";
                }
                if (elements[j] != "  "){
                    cout << "/\\";
                } else {
                    cout << "  ";
                }
            }
            for (int k = 0; k < (dlinaStroki - int(pow(2.0, i))) / (int(pow(2.0, i)) + 1) + dlinaStroki % 2; k++){
                cout << " ";
            }
            cout << endl;
        }
    }

    void deleteTree(){
        if (root != nullptr){
            root->deleteNode();
            delete(this);
        } else {
            cout << "Дерево мертво" << endl;
        }
    }
private:
    Node *root;

    vector<int> path(int element){
        vector<int> returnPath;
        while(element != 1){
            returnPath.emplace(returnPath.begin(), element % 2);
            element /= 2;
        }
        return returnPath;
    }
};

Tree* createTree(){
    Tree *newtree;
    newtree = new Tree();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);
    for (int i = 0; i < 10; i++){
        newtree->addNode(distrib(gen));
    }
    return newtree;
}

void func(Tree* tree, int numberOfFunc){
    if (numberOfFunc == 1){
        cout << "Введите значение, добавляемое в дерево: ";
        int newValue;
        cin >> newValue;
        tree->addNode(newValue);
        numberOfFunc = -1;
    } else if (numberOfFunc == 2){
        cout << "Введите значение, удаляемое из дерева: ";
        int deleteValue;
        cin >> deleteValue;
        tree->deleteValue(deleteValue);
        numberOfFunc = -1;
    } else if (numberOfFunc == 3){
        tree->deleteTree();
        numberOfFunc = -1;
    } else if (numberOfFunc == 4){
        cout << "Длина дерева: " << tree->depthTree() << endl;
        numberOfFunc = -1;
    } else if (numberOfFunc == 5){
        cout << "Введите искомое значение: ";
        int searchValue;
        cin >> searchValue;
        tree->searchNode(searchValue);
        numberOfFunc = -1;
    } else if (numberOfFunc == 6){
        tree->printTree();
        numberOfFunc = -1;
    } else if (numberOfFunc == -1){
        cin >> numberOfFunc;
    } else { }
}

int main(){
    Tree *tree;
    tree = createTree();
    while(true){
        cout << "Выберите функцию:\n1) Добавить значение в дерево\n2) Удалить значение из дерева\n3) Удалить дерево\n4) Узнать глубину дерева\n5) Есть ли значение в дереве\n6) Вывести дерево\nФункция: ";
        int numberOfFunc;
        cin >> numberOfFunc;
        func(tree, numberOfFunc);
    }
    return 0;
}