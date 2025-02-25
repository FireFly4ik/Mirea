#include <iostream>
#include <set>
using namespace std;

class Node{
public:
    Node(int newHashId, string number){
        hashId = newHashId;
        numbers.push_back(number);
    }
    
    void search(int valueToSearch){
        if (hashId == valueToSearch){
            for (int i = 0; i < numbers.size(); i++){
                cout << numbers[i] << endl;
            }
        } else {
            if (leftNode != nullptr){
                if (valueToSearch < hashId){
                    return leftNode->search(valueToSearch);
                } else {
                    cout << "Человека нет в телефонной книге" << endl;
                }
            } 
            if (rightNode != nullptr){
                if (valueToSearch > hashId){
                    return rightNode->search(valueToSearch);
                } else {
                    cout << "Человека нет в телефонной книге" << endl;
                }
            }
        }
    }

    void addNode(int newValue, string number){
        if (newValue < hashId){
            if (leftNode == nullptr){
                leftNode = new Node(newValue, number);
            } else {
                leftNode->addNode(newValue, number);
            }
        } else if (newValue > hashId){
            if (rightNode == nullptr){
                rightNode = new Node(newValue, number);
            } else {
                rightNode->addNode(newValue, number);
            }
        } else {
            set<string> setNumbers {numbers.begin(), numbers.end()};
            if (setNumbers.count(number)){
                cout << "У данного человека уже есть такой номер" << endl;
            } else {
                numbers.push_back(number);
            }
        }
    }
    
    void deleteValue(int valueToDelete){
        if (valueToDelete == hashId){
            cout << "Какой номер удалить?" << endl;
            for (int i = 0; i < numbers.size(); i++){
                cout << i << " " << numbers[i] << endl;
            }
            cout << "Вариант: ";
            int id;
            cin >> id;
            if (0 < id < numbers.size()){
                numbers.erase(numbers.begin() + id);
                cout << "Номер удалён" << endl;
                return;
            }
        }
        if (valueToDelete < hashId){
            if (leftNode != nullptr){
                leftNode->deleteValue(valueToDelete);
                if (leftNode->getNumbersLen() == 0){
                    if (leftNode->getRight() == nullptr and leftNode->getLeft() == nullptr){
                        leftNode = nullptr;
                    } else if (leftNode->getRight() != nullptr){
                        numbers = leftNode->returnMaxNumbers();
                        hashId = leftNode->returnMax();
                    } else {
                        numbers = leftNode->getNumbers();
                        hashId = leftNode->getHashId();
                        leftNode = leftNode->getLeft();
                    }
                }
            } else {
                cout << "Номера нет в телефонной книге" << endl;
            }
        } else {
            if (rightNode != nullptr){
                rightNode->deleteValue(valueToDelete);
                if (rightNode->getNumbersLen() == 0){
                    if (rightNode->getRight() == nullptr and rightNode->getLeft() == nullptr){
                        rightNode = nullptr;
                    } else if (rightNode->getLeft() != nullptr){
                        numbers = rightNode->returnMinNumbers();
                        hashId = rightNode->returnMin();
                    } else {
                        numbers = rightNode->getNumbers();
                        hashId = rightNode->getHashId();
                        leftNode = rightNode->getRight();
                    }
                }
            } else {
                cout << "Номера нет в телефонной книге" << endl;
            }
        }
    }


private:
    Node *leftNode = nullptr;
    Node *rightNode = nullptr;
    int hashId;
    vector<string> numbers;

    vector<string> getNumbers(){
        return numbers;
    }

    int getHashId(){
        return hashId;
    }

    int getNumbersLen(){
        return numbers.size();
    }

    Node* getLeft(){
        return leftNode;
    }

    Node* getRight(){
        return rightNode;
    }

    int returnMax(){
        if (rightNode == nullptr){
            return hashId;
        } else {
            int valueToReturn = rightNode->returnMax();
            if (rightNode->getHashId() == valueToReturn){
                rightNode = nullptr;
            }
            return valueToReturn;
        }
    }

    vector<string> returnMaxNumbers(){
        if (rightNode == nullptr){
            return numbers;
        } else {
            return rightNode->returnMaxNumbers();
        }
    }

    int returnMin(){
        if (leftNode == nullptr){
            return hashId;
        } else {
            int valueToReturn = leftNode->returnMin();
            if (leftNode->getHashId() == valueToReturn){
                leftNode = nullptr;
            }
            return valueToReturn;
        }
    }

    vector<string> returnMinNumbers(){
        if (leftNode == nullptr){
            return numbers;
        } else {
            return leftNode->returnMinNumbers();
        }
    }

};

class Tree{
public:
    void addNode(int newValue, string number){
        if (root == nullptr){
            root = new Node(newValue, number);
        } else {
            root->addNode(newValue, number);
        }
    }

    void searchNode(int value){
        if (root != nullptr){
            root->search(value);
        } else {
            cout << "Телефонная книга пуста" << endl;
        }
    }

    void deleteValue(int value){
        root->deleteValue(value);
    }

private:
    Node *root;

};

int hashFunc(string value){
    int hashID = 0;
    for (int i = 0; i < value.length(); i++){
        hashID += (int) value[i];
    }
    return hashID;
}

void func(Tree* tree, int numberOfFunc){
    if (numberOfFunc == 1){
        cout << "Введите контакт, добавляемый в телефонную книгу: ";
        string newValue, number;
        cin >> newValue;
        cout << "Введите номер телефона: ";
        cin >> number;
        int hashID = hashFunc(newValue);
        tree->addNode(hashID, number);
        numberOfFunc = -1;
    } else if (numberOfFunc == 2){
        cout << "Введите контакт: ";
        string deleteValue;
        cin >> deleteValue;
        tree->deleteValue(hashFunc(deleteValue));
        numberOfFunc = -1;
    } else if (numberOfFunc == 3){
        cout << "Введите искомый контакт: ";
        string searchValue;
        cin >> searchValue;
        tree->searchNode(hashFunc(searchValue));
    } else { }
}

int main(){
    Tree *tree;
    tree = new Tree;
    while(true){
        cout << "Выберите функцию:\n1) Добавить контакт в телефонную книгу\n2) Удалить контакт из телефонной книги\n3) Найти номера по имени\nФункция: ";
        int numberOfFunc;
        cin >> numberOfFunc;
        func(tree, numberOfFunc);
    }
    return 0;
}