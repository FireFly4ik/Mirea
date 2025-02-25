#include <iostream>
#include <vector> 
using namespace std;

void viravnivanie (vector<int> &num1, vector<int> &num2){
    while (num1.size() < num2.size()){
        num1.emplace(num1.begin(), 0);
    }
    while (num1.size() > num2.size()){
        num2.emplace(num2.begin(), 0);
    }
}

int sravnenieVectorov(vector<int> v1, vector<int> v2){
    if (v1.size() > v2.size()){
        return 1;
    } else if (v2.size() > v1.size()){
        return -1;
    } else {
        for (int i = 0; i < v1.size(); i++){
            if (v1[i] > v2[i]){
                return 1;
            } else if (v2[i] > v1[i]) {
                return -1;
            }
        }
    }
    return 0;
}

void show_vector(vector<int>a)
{
    while (a[0] == 0 and a.size() > 0) {
        a.erase(a.begin());
    }
    if (a.empty()){
        cout << "0" << endl;
        return;
    }
    for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it){
        if(it == a.begin() && *it == 0 && a.size() != 1){
            continue;
        }
        cout<<*it;
    }
    cout << endl;
}

void sozdanieVectoraChisla(vector<int> &vec, string chislo){
    while (chislo.length() > 0){
        char q = chislo[0];
        string i = "";
        i = q;
        vec.emplace(vec.end(), stoi(i));
        chislo.erase(0, 1);
    }
}

vector<int> vichitanie(vector<int> v1, vector<int> v2){
    vector<int> nul = {0};
    if (sravnenieVectorov(v1, v2) == -1){
        v1.swap(v2);
    } else if (sravnenieVectorov(v1, v2) == 0){
        return nul;
    }
    vector<int> itog (v1.size());
    viravnivanie(v1, v2);
    for (int i = v1.size() - 1; i > -1; i--){
        itog[i] += v1[i] - v2[i];
        if (itog[i] < 0){
            itog[i - 1]--;
            itog[i] += 10;
        }
    }
    while (itog[0] == 0 and itog.size() != 1){
        itog.erase(itog.begin());
    }
    return itog;
}

vector<int> sum(vector<int> v1, vector<int> v2){
    if (sravnenieVectorov(v1, v2) == -1){
        v1.swap(v2);
    }
    viravnivanie(v1,v2);
    vector<int> itog (v1.size() + 1);
    for (int i = v1.size() - 1; i > -1; i--){
        itog[i + 1] += v1[i] + v2[i];
        if (itog[i + 1] > 9){
            itog[i]++;
            itog[i + 1] -= 10;
        }
    }
    if (itog[0] == 0){
        itog.erase(itog.begin());
    }
    return itog;
}

vector<int> umnozhenie(vector<int> v1, vector<int> v2){
    vector<int> itog (v1.size() + v2.size());
    for (int i = v1.size() - 1; i > -1; i--){
        for (int j = v2.size() - 1; j > -1; j--){
            itog[i + j + 1] += v1[i] * v2[j] % 10;
            if (itog[i + j + 1] > 9) {
                itog[i + j + 1] -= 10;
                itog[i + j] += 1;
            }
            itog[i + j] += v1[i] * v2[j] / 10;
        }
    }
    if (itog[0] == 0){
        itog.erase(itog.begin());
    }
    return itog;
}

vector<int> delenie (vector<int> v){
    vector<int> itog(v.size());
    int chislo = 0;
    for (int i = 0; i < v.size(); i++){
        if (chislo == 1){
            itog[i] = (chislo * 10 + v[i]) / 2;
            chislo = (chislo * 10 + v[i]) % 2;
        } else {
            if (v[i] < 2){
                chislo = v[i];
            } else {
                chislo = chislo * 10 + v[i];
                itog[i] = chislo / 2;
                chislo = chislo % 2;
            }        
        }
    }
    if (itog[0] == 0){
        itog.erase(itog.begin());
    }
    return itog;
}

int main(){
    string delimoeString, delitelString;
    vector<int> delimoe, delitel;
    cin >> delimoeString >> delitelString;
    sozdanieVectoraChisla(delimoe, delimoeString);
    sozdanieVectoraChisla(delitel, delitelString);
    vector<int> l = {0}, r = delimoe, edin = {1}, nul = {0};
    vector<int> polovina = delenie(sum(r, l));
    if (delitel == nul){
        cout << "На ноль делить нельзя!!!" << endl;
        return 0;
    }
    if (delimoe == nul){
        cout << "0" << endl;
        return 0;
    }
    while ((sravnenieVectorov(vichitanie(delimoe, umnozhenie(polovina, delitel)), delitel) != -1 or sravnenieVectorov(umnozhenie(polovina, delitel), delimoe) == 1) and vichitanie(r, l) != edin ){
        polovina = delenie(sum(r, l));
        if (sravnenieVectorov(delimoe, umnozhenie(delitel, polovina)) == 1){
            l = polovina;
        } else if (sravnenieVectorov(delimoe, umnozhenie(delitel, polovina)) == -1){
            r = polovina;
        } else {
            cout << "Частное: ";
            show_vector(polovina);
            return 0;
        }
    }
    if (sravnenieVectorov(delimoe, umnozhenie(delitel, polovina)) == 0){
        cout << "Частное: ";
        show_vector(polovina);
        return 0;
    } else {
        cout << "Частное: ";
        show_vector(polovina);
        cout << "Остаток: ";
        show_vector(vichitanie(delimoe, umnozhenie(delitel, polovina)));
        return 0;
    }
    // vector<int> a = {1,2}, b = {1, 3};
    // show_vector(vichitanie(a,b));
    return 0;
}