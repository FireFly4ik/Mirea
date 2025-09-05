#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int priority;
    string data;
};

struct Heap {
    string findMax(){
        if (heap.size() == 0) {
            return "Заданий нет";
        }
        return heap[0]->data;
    }

    void deleteMax(){
        Node* max = heap[0];
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        int i = 0;
        while (true) {
            int next = i;
            if (2 * i + 1 < heap.size() and heap[2 * i + 1]->priority > heap[next]->priority) {
                next = 2 * i + 1;
            }
            if (2 * i + 2 < heap.size() and heap[2 * i + 2]->priority > heap[next]->priority) {
                next = 2 * i + 2;
            }
            if (next == i) break;
            swap(heap[i], heap[next]);
            i = next;
        }
    }

    void addNode(string data, int priority){
        Node* newNode = new Node;
        newNode->priority = priority;
        newNode->data = data;
        heap.push_back(newNode);
        int i = heap.size() - 1;
        while (i > 0 and priority > heap[(i - 1) / 2]->priority){
            swap(heap[i],  heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void editPriority (int x){
        int i = 0;
        heap[i]->priority = x;
        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < heap.size() && heap[left]->priority > heap[largest]->priority) {
                largest = left;
            }
            if (right < heap.size() && heap[right]->priority > heap[largest]->priority) {
                largest = right;
            }
            
            if (largest == i) 
                break;
            
            swap(heap[i], heap[largest]);
            i = largest;
        }
        
        i = 0;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent]->priority >= heap[i]->priority) 
                break;
            
            swap(heap[i], heap[parent]);
            i = parent;
        }
    }

    void deleteAll() {
        for (int i = 0; i < heap.size(); i++){
            delete heap[i];
        }
        delete this;
    }

    vector<Node*> heap;
};

void vibirator(){
    cout << "1. Добавить задание\n";
    cout << "2. Показать близжайшее задание\n";
    cout << "3. Завершить задание\n";
    cout << "4. Изменить приоритет ближайшего задания\n";
    cout << "5. Завершить\n";
    cout << "Ваш выбор: ";
}

int main(){
    Heap* heap = new Heap;
    while (true) {
        int l;
        vibirator();
        cin >> l;
        if (l == 5){
            heap->deleteAll();
            break;
        } else if (l == 1){
            string data;
            cout << "Введите заданиe: ";
            cin >> data;
            int priority;
            cout << "Введите приоритет задания: ";
            cin >> priority;
            heap->addNode(data, priority);
        } else if (l == 3){
            heap->deleteMax();
        } else if (l == 2){
            cout << "Ближайшее задание: " << heap->findMax() << endl;
        } else if (l == 4){
            int newPriority;
            cout << "Введите новый приоритет ближайшего задания: ";
            cin >> newPriority;
            heap->editPriority(newPriority);
        } else {
            cout << "Неверный ввод. Попробуйте снова." << endl;
        }
    }
    return 0;
}