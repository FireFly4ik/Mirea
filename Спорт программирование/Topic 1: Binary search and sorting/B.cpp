#include <iostream>
#include <vector>
#include <string>
using namespace std;

int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid; 
        } 
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(){
    vector<string> answers;
    int t, x1, x2;
    cin >> t;
    for (int i = 0; i < t; i++){
        vector<int> operations;
        cin >> x1 >> x2;
        if ((x1 + x2) % 3 == 0){
            while (x1 > 0 and x2 > 0){
                int del = min(x1, x2);
                while (del * 2 > max(x1, x2) or binarySearch(operations, del) != -1){
                    del--;
                }
                if (min(x1, x2) == x1){
                    x1 -= del;
                    x2 -= del * 2;
                } else {
                    x2 -= del;
                    x1 -= del * 2;      
                }
                operations.emplace(operations.begin(), del);
                quickSort(operations, 0, operations.size() - 1);
            }
            if (x1 == 0 and x2 == 0){
                answers.push_back("yes");
            } else {
                answers.push_back("no");
            }
        } else {
            answers.push_back("no");
        }
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
}