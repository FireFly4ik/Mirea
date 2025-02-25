#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sozdanieVectora(string chislo, vector<int> &vec){
    while (chislo.length() > 0){
        char q = chislo[0];
        string i = "";
        i = q;
        vec.emplace(vec.end(), stoi(i));
        chislo.erase(0, 1);
    }
}

bool check(vector<int> &v){
    for (int i = 0; i < v.size(); i++){
        if (v[i] != 0){
            return true;
        }
    }
    return false;
}

int show_vector(vector<int>&a)
{
    for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it){
        cout<<*it;
    }
    cout << endl;
    return 0;
}

bool proverka(vector<int> &v){
    for (int i = 0; i < v.size(); i++){
        if (v[i] > 1){
            return true;
        }
    }
    return false;
}

vector<int> sum(vector<int> a, vector<int> b){
    vector<int> c(a.size());
    for (int i = a.size() - 1; i > -1; i --){
        a[i] += b[i];
        if (a[i] > 1){
            a[i] -= 2;
            if (i == 0){
                c.emplace(c.begin(), 1);
                a.emplace(a.begin(), 0);
            } else {
                c[i - 1] += 1;
            }
        }
    }
    cout << endl;
    show_vector(a);
    show_vector(c);
    if (check(c)){
        return sum(a, c);
    } else {
        return a;
    }
}

int main(){
    string n1, n2, q;
    vector<int> v1, v2, minusa;
    cin >> n1 >> n2;
    sozdanieVectora(n1, v1);
    sozdanieVectora(n2, v2);
    while (proverka(v1) || proverka(v2)){
        cout << "Введите корректные числа!!!" << endl;
        cin >> n1 >> n2;
        v1.clear();
        v2.clear();
        sozdanieVectora(n1, v1);
        sozdanieVectora(n2, v2);
    }

    while  (v1.size() < v2.size()){
        v1.emplace(v1.begin(), 0);
    }
    while  (v2.size() < v1.size()){
        v2.emplace(v2.begin(), 0);
    }
    vector<int> itog = sum(v1, v2);
    cout << endl;
    show_vector(itog);
    return 0;
}