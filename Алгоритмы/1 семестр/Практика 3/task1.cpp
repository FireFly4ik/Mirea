#include <iostream>
#include <vector>
#include <string>
using namespace std;

int rev = 0;

void sozdanieVectoraChisla(vector<int> &vec, string chislo){
    while (chislo.length() > 0){
        char q = chislo[0];
        string i = "";
        i = q;
        vec.emplace(vec.end(), stoi(i));
        chislo.erase(0, 1);
    }
}

void show_vector(vector<int>&a, bool reverse)
{
    if (reverse){
        cout << "-";
    }
    for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it){
        if(it == a.begin() && *it == 0 && a.size() != 1){
            continue;
        }
        cout<<*it;
    }
    cout << endl;
}

vector<int> sum(vector<int> &v1, vector<int> &v2, bool reverse, bool vuvod, bool minusBool){
    vector<int> v3(v1.size() + 1);
    int minus = v1.size() - v2.size();
    for (int i = v1.size() - 1; i != -1 ; i--){
        int plus;
        if (i >= minus){
            plus = v1[i] + v2[i - minus];
        } else {plus = v1[i];}
        v3[i + 1] += plus;
        if (v3[i + 1] >= 10){
            v3[i + 1] -= 10;
            v3[i] += 1;
        }
    }
    if (vuvod){
        cout << (reverse ? "Разность: " : "Сумма: ");
        show_vector(v3, minusBool);
    }
    return v3;
}

vector<int> vuchitanie(vector<int> &v1, vector<int> &v2, bool reverse, bool vuvod, bool minus){
    vector<int> v3(v1.size());
    int minusRazr = v1.size() - v2.size();
    for (int i = v1.size() - 1; i != -1 ; i--){
        int minus;
        if (i >= minusRazr){
            minus = v1[i] - v2[i - minusRazr];
        } else {minus = v1[i];}
        v3[i] += minus;
        if (v3[i] < 0){
            v3[i] += 10;
            v3[i - 1] -= 1;
        }
    }
    if (vuvod){
        cout << (reverse ? "Сумма: " : "Разность: ");
        show_vector(v3, minus);
    }
    return v3;
}

string sravnS(string s1, string s2, bool maximum){
    if (s1.length() > s2.length()){
        return maximum ? s1 : s2;
    } else if (s2.length() > s1.length()){
        return maximum ? s2 : s1;
    } else {
        for (int i = 0; i < s1.length(); i++){
            if (s1[i] > s2[i]){
                return maximum ? s1 : s2;
            } else if (s2[i] > s1[i]){
                return maximum ? s2 : s1;
            }
        }
    }
    return s1;
}

int main(){
    string n1, n2;
    cin >> n1 >> n2;
    if (n1[0] == '-'){
        rev += 1;
        n1.erase(0,1);
    }
    if (n2[0] == '-'){
        rev += 2;
        n2.erase(0,1);
    }
    vector<int> num1, num2;
    switch (rev){
        case 0:
            sozdanieVectoraChisla(num1, sravnS(n1, n2, true));
            sozdanieVectoraChisla(num2, sravnS(n1, n2, false));
            sum(num1, num2, 0, 1, 0);
            vuchitanie(num1, num2, 0, 1, 0);
            break;
        case 1:
            if (sravnS(n1, n2, true) == n1) {
                sozdanieVectoraChisla(num1, n1);
                sozdanieVectoraChisla(num2, n2);
                vuchitanie(num1, num2, 1, 1, 1);
                sum(num1, num2, 1, 1, 0);
            } else {
                sozdanieVectoraChisla(num1, n2);
                sozdanieVectoraChisla(num2, n1);
                vuchitanie(num1, num2, 1, 1, 0);
                sum(num1, num2, 1, 1, 0);
            }
            break;
        case 2:
            if (sravnS(n1, n2, true) == n2) {
                sozdanieVectoraChisla(num1, n2);
                sozdanieVectoraChisla(num2, n1);
                vuchitanie(num1, num2, 1, 1, 1);
                sum(num1, num2, 1, 1, 0);
            } else {
                sozdanieVectoraChisla(num1, n1);
                sozdanieVectoraChisla(num2, n2);
                vuchitanie(num1, num2, 1, 1, 0);
                sum(num1, num2, 1, 1, 0);
            }
            break;
        case 3:
            sozdanieVectoraChisla(num1, sravnS(n1, n2, false));
            sozdanieVectoraChisla(num2, sravnS(n1, n2, true));
            sum(num1, num2, 0, 1, 1);
            vuchitanie(num2, num1, 0, 1, 0);
            break;
    }
    return 0;
}