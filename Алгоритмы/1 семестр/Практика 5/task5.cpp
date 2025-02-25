#include <iostream>
using namespace std;

void pokazatVector(vector<int>&a)
{
    for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it){
        cout<<*it<< " ";
    }
    cout << endl;
}

void sortirovka(vector<int> &vec){
    int sorted = 0, shag = vec.size() / 3;
    while (shag >= 1){
        for (int povt = 0; povt < shag; povt++){
            for (int i = povt + shag; i < vec.size(); i += shag){
                for (int j = povt; j < i; j += shag){
                    if (vec[i] <= vec[j]){
                        vec.emplace(vec.begin() + j, vec[i]);
                        vec.erase(vec.begin() + i + 1);
                        break;
                    }
                }
            }
        }
        shag /= 5;
    }
    for (int i = 1; i < vec.size(); i ++){
        for (int j = 0; j < i; j ++){
            if (vec[i] <= vec[j]){
                vec.emplace(vec.begin() + j, vec[i]);
                vec.erase(vec.begin() + i + 1);
                break;
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