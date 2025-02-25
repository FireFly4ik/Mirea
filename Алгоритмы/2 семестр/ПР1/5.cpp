#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* nextNode = nullptr;
};

class Spisok{
public:
    bool reversed;
    int length = 0;

    void addNode(int x){
        if (head == nullptr){
            head = new Node;
            head->data = x;
            length++;
            return;
        }
        Node* last = head;
        while(last->nextNode != nullptr){
            last = last->nextNode;
        }
        Node* newNode = new Node;
        newNode->data = x;
        last->nextNode = newNode;
        length++;
    }

    void reverseNodes(){
        head = reverseNodesHead(head);
    }

    void sumSpiski(Spisok* other){
        if (!reversed){
            reverseNodes();
        }
        if (!other->reversed){
            other->reverseNodes();
        }
        Node* lastOther = other->head;
        Node* last = head;
        Node* nullNode = new Node;
        nullNode->data = 0;
        while (true) {
            last->data += lastOther->data;
            if (last->data > 9){
                last->data -= 10;
                if (last->nextNode != nullptr){
                    last->nextNode->data ++;
                } else {
                    addNode(1);
                }
            }
            if (last->nextNode != nullptr){
                last = last->nextNode;
            } else {
                return;
            }
            if (lastOther->nextNode != nullptr){
                lastOther = lastOther->nextNode;
            } else {
                lastOther = nullNode;
            }
        }
    }

    void reversePrintNodes(Node* last = nullptr){
        if (last == nullptr){
            last = head;
        }
        if (last->nextNode != nullptr){
            reversePrintNodes(last->nextNode);
        }
        cout << last->data << " ";
    }

private:
    Node* head = nullptr;

    Node* reverseNodesHead(Node* last, Node* previousNode = nullptr){
        if (last->nextNode != nullptr){
            Node* temp = last->nextNode;
            last->nextNode = previousNode;
            return reverseNodesHead(temp, last);
        } else {
            last->nextNode = previousNode;
            return last;
        }
}
};

void createSpiski(Spisok* first, Spisok* second){
    bool reversed = false;
    cout << "Вводится в обратном порядке?(0/1): ";
    cin >> reversed;
    first->reversed = reversed;
    int n, x;
    cout << "Какая длина числа?: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> x;
        first->addNode(x);
    }
    cout << "Вводится в обратном порядке?(0/1): ";
    cin >> reversed;
    second->reversed = reversed;
    cout << "Какая длина числа?: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> x;
        second->addNode(x);
    }
    
}

int main(){
    Spisok* first = new Spisok;
    Spisok* second = new Spisok;
    createSpiski(first, second);
    if (first->length >= second->length){
        first->sumSpiski(second);
    } else {
        second->sumSpiski(first);
    }
    first->reversePrintNodes();
    cout << endl;
    return 0;
}