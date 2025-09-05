#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Heap {
    vector<int> heap;

    void heapBuild(int n, int i){
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n and heap[largest] > heap[left]) {
            largest = left;
        }
        if (right < n and heap[largest] > heap[right]) {
            largest = right;
        }
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapBuild(n, largest);
        }
    }

    void heapFromVec(vector<int>& vec) {
        heap = vec;
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            heapBuild(heap.size(), i);
        }
        for (int i = heap.size() - 1; i > 0; --i) {
            swap(heap[0], heap[i]);
            heapBuild(i, 0);
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
};

int main() {
    Heap* heap = new Heap;
    vector<int> vec = {70, 65, 60, 28, 43, 54, 45, 76, 94, 10, 87, 2};
    heap->heapFromVec(vec);
    heap->print();
    return 0;
}