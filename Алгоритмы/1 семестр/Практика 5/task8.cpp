#include <iostream>
using namespace std;

void pokazatVector(vector<int>&a)
{
    for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it){
        cout<<*it<< " ";
    }
    cout << endl;
}

int binar(vector<int> &vec, int r, int vstavka){
    int l = 0;
    int mid = (l + r) / 2;
    while (true) {
        if (vstavka == vec[mid]){
            return mid;
        }
        if (vstavka > vec[mid]){
            l = mid;
            mid = (l + r) / 2;
        } else if (vstavka < vec[mid]){
            r = mid;
            mid = (l + r) / 2;
        }
        if (r - 1 == l){
            return (vec[l] > vstavka ? l : r);
        }
    }
}

void sortirovka(vector<int> &vec){
    for (int i = 1; i < vec.size(); i++){
        vec.emplace(vec.begin() + binar(vec, i, vec[i]), vec[i]);
        vec.erase(vec.begin() + i + 1);
    }
}

int main(){
    vector<int> obrazec1 = {31,32,9,44,24,50,27,34,42,29,4,20,26,18,5,21,48,16,35,41,40,17,38,10,45,14,25,6,3,13,22,46,47,8,23,7,15,39,2,37,1,19,28,49,43,30,12,11,36,33};
    sortirovka(obrazec1);
    pokazatVector(obrazec1);
    return 0;
}