#include <iostream>
#include <algorithm>
using namespace std;

struct Heap {
    Heap(vector<int>* massive){
        createHeap(massive);
    }
    Heap() {};

    void createHeap(vector<int>* massive){
        heap = *massive;
        sort(heap.begin(), heap.end());
    }

    int deleteMin(){
        int min = heap[0];
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        int i = 0;
        while (true) {
            int next = i;
            if (2 * i + 1 < heap.size() and heap[2 * i + 1] < heap[next]) {
                next = 2 * i + 1;
            }
            if (2 * i + 2 < heap.size() and heap[2 * i + 2] < heap[next]) {
                next = 2 * i + 2;
            }
            if (next == i) break;
            swap(heap[i], heap[next]);
            i = next;
        }
        return min;
    }

    void add(int data){
        heap.push_back(data);
        int i = heap.size() - 1;
        while (i > 0 and data < heap[(i - 1) / 2]){
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

    int svyazat(){
        int answ = 0;
        while (heap.size() > 1){
            int a = deleteMin();
            int b = deleteMin();
            add(a + b);
            answ += a + b;
            cout << answ << endl;
        }
        return answ;
    }

    vector<int> heap;
};

int main(){
    Heap* heap = new Heap();
    int l;
    cin >> l;
    vector<int> massive;
    for (int i = 0; i < l; i++){
        int data;
        cin >> data;
        massive.push_back(data);
    }
    heap->createHeap(&massive);
    heap->svyazat();
    delete heap;
    return 0;
}