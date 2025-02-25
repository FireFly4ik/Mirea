#include <iostream>
using namespace std;

void pokazatVector(vector<int>&a)
{
    for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it){
        cout<<*it<< " ";
    }
    cout << endl;
}

void sortirovka(vector<int> &vec, int l, int r){
    if (r - l <= 1){
        return;
    }
    int opora = vec[l];
    int left = l + 1, right = r - 1, povtor = 0;
    while (true){
        while(left < vec.size() and vec[left] < opora){
            left++;
        }
        while(right > 0 and vec[right] >= opora){
            right--;
        }
        if (left >= right){
            break;
        } else {
            swap(vec[left], vec[right]);
        }
    }
    swap(vec[l], vec[left - 1]);
    sortirovka(vec, l, left - povtor);
    sortirovka(vec, left, r);
}

int main(){
    vector<int> obrazec = {31,32,9,44,24,50,27,34,42,29,4,20,26,18,5,21,48,16,35,41,40,17,38,10,45,14,25,6,3,13,22,46,47,8,23,7,15,39,2,37,1,19,28,49,43,30,12,11,36,33};
    sortirovka(obrazec, 0, obrazec.size());
    pokazatVector(obrazec);
    return 0;
}