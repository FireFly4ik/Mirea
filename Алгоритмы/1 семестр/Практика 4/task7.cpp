#include <iostream>
#include <vector>
using namespace std;

void show_vector(vector<int> &vec){
    for (int i = 0; i < vec.size(); i ++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

int main(){
    vector<int> hash (7);
    for (int i = 0; i < 7; i ++){
        int chislo;
        cin >> chislo;
        int index = chislo % 7;
        if (hash[index] == 0){
            hash[index] = chislo;
        } else {
            for (int j = index + 1; j < index + 8; j++){
                if (hash[j % 7] == 0){
                    hash[j % 7] = chislo;
                    break;
                }
            }
        }
    }
    show_vector(hash);
    return 0;
}