#include <iostream> 
#include <vector>
using namespace std;

void pokazatVector(vector<int>&a)
{
    for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it){
        cout << *it << " ";
    }
    cout << endl;
}

void sortirovka(vector<int> &vec){
    int k;
    while (true){
        if (k == vec.size() - 1){
            break;
        }
        k = 0;
        for (int i = 0; i < vec.size() - 1; i++){
            if (vec[i] > vec[i + 1]){
                swap(vec[i], vec[i + 1]);
            } else {
                k++;
            }
        }
    } 
}

int main(){
    vector<int> obrazec1 = {31,32,9,44,24,50,27,34,42,29,4,20,26,18,5,21,48,16,35,41,40,17,38,10,45,14,25,6,3,13,22,46,47,8,23,7,15,39,2,37,1,19,28,49,43,30,12,11,36,33};
    sortirovka(obrazec1);
    pokazatVector(obrazec1);
    return 0;
}