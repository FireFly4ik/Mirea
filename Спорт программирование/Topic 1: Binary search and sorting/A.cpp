#include <iostream>
#include <vector>
using namespace std;

int binarySearchRecursive(const std::vector<int>& arr, int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid + 1; 
	    }
        if (arr[mid] > target) {
            return binarySearchRecursive(arr, left, mid - 1, target);
        } else if (arr[mid  + 1] > target) {
            return mid + 1;
        } else {
            return binarySearchRecursive(arr, mid + 1, right, target);
        }
    }
    return -1;
}

int main(){
    int n, k, vr = 240;
    cin >> n >> k;
    vr -= k;
    vector<int> timeToSolve{0};
    for (int i = 0; i < n; i++){
        timeToSolve.push_back(timeToSolve[timeToSolve.size() - 1] + 5 * (i + 1));
    }
    timeToSolve.erase(timeToSolve.begin());
    if (vr < 5){
        cout << 0 << endl;
    } else if (vr > timeToSolve[timeToSolve.size() - 1]) {
        cout << timeToSolve.size() << endl;
    } else {
        cout << binarySearchRecursive(timeToSolve, 0, timeToSolve.size() - 1, vr) << endl;
    }
    return 0;
}