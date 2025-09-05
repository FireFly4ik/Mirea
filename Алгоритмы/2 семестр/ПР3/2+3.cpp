#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Heap {
    Heap(vector<int>* massive){
        heap = *massive;
        sort(heap.begin(), heap.end());
        reverse(heap.begin(), heap.end());
    }
    Heap() {};

    int findMax(){
        return heap[0];
    }

    int deleteMax(){
        int max = heap[0];
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        int i = 0;
        while (true) {
            int next = i;
            if (2 * i + 1 < heap.size() and heap[2 * i + 1] > heap[next]) {
                next = 2 * i + 1;
            }
            if (2 * i + 2 < heap.size() and heap[2 * i + 2] > heap[next]) {
                next = 2 * i + 2;
            }
            if (next == i) break;
            swap(heap[i], heap[next]);
            i = next;
        }
        return max;
    }

    void add(int data){
        heap.push_back(data);
        int i = heap.size() - 1;
        while (i > 0 and data > heap[(i - 1) / 2]){
            swap(heap[i],  heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void print(int index = 0, int space = 0) {
        if (index >= heap.size() || !heap[index]) return;
        space += 2;
        print(2 * index + 2, space);
        for (int i = 2; i < space; ++i) {
            cout << " ";
        }
        cout << heap[index] << std::endl;
        print(2 * index + 1, space);
    }

    vector<int> heap;
};

void sliyanie(Heap* heap1, Heap* heap2){
    for (int i = 0; i < heap2->heap.size(); i++){
        heap1->heap.push_back(heap2->heap[i]);
    }
    sort(heap1->heap.begin(), heap1->heap.end());
    reverse(heap1->heap.begin(), heap1->heap.end());
}

int main(){
    int l;
    cin >> l;
    vector<int> massive;
    for (int i = 0; i < l; i++){
        int x;
        cin >> x;
        massive.push_back(x);
    }
    Heap* heap = new Heap;
    heap->createHeap(&massive);
    heap->deleteMax();
    heap->add(5);
    heap->print();
    delete heap;
    return 0;
}