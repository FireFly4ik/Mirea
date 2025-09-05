#include <iostream>
using namespace std;

struct Node{
    Node* next = nullptr;
    int key;
    int priority;
};

struct Queue{
    Node* head;
    int maxPriority;
    
    void addNode(int key, int priority){
        if (priority > maxPriority){
            maxPriority = priority;
        }
        Node* newNode = new Node;
        newNode->key = key;
        newNode->priority = priority;
        newNode->next = nullptr;
        if (!head){
            head = newNode;
            return;
        }
        Node* last = head;
        while (last->next){
            last = last->next;
        }
        last->next = new Node();
        last->next->key = key;
        last->next->priority = priority;
    }

    void deleteMax(){
        if (!head) return;
        Node* prev = nullptr;
        Node* last = head;
        while (last->priority != maxPriority){
            prev = last;
            last = last->next;
        }
        if (!prev){
            head = last->next;
        } else {
            prev->next = last->next;
        }
        delete last;
        last = head;
        int newMaxPriority = head->priority;
        while (last->next){
            if (last->next->priority > maxPriority){
                maxPriority = last->next->priority;
            }
            last = last->next;
        }
        maxPriority = newMaxPriority;
    }

    void deleteAll(){
        Node* last = head;
        while (last){
            Node* temp = last;
            last = last->next;
            delete temp;
        }
        delete this;
    }

    void print(){
        Node* last = head;
        while (last){
            cout << last->key << "(" << last->priority << ") ";
            last = last->next;
        }
        cout << endl;
    }
};

int main(){
    Queue* queue = new Queue;
    int l;
    cin >> l;
    for (int i = 0; i < l; i++){
        int data;
        cin >> data;
        int priority;
        cin >> priority;
        queue->addNode(data, priority);
    }
    queue->print();
    queue->deleteMax();
    queue->print();
    return 0;
}