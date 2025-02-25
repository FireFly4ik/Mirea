#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isNumber(char s){
    if (s == '1' or s == '2'  or s == '3'  or s == '4' or s == '5'  or s == '6' or s == '7' or s == '8'  or s == '9' or s == '0'){
        return true;
    }
    return false;
}

int ctoi(char c){
    string i = "";
    i = c;
    return stoi(i);
}

string toDvoich(int x){
    string q;
    while (x > 0){
        q = to_string(x % 2) + q;
        x /= 2;
    }
    return q;
}

string slice(string &v, int nach, int kon){
    string slicedVector;
    for (int i = nach; i < kon; i++){
        slicedVector.push_back(v[i]);
    }
    return slicedVector;
}

int chisloRazr(int x){
    int q = 1;
    while (x > 0){
        q += 1;
        x /= 10;
    }
    return q;
}

int main(){
    string line;
    ifstream text("hello.txt");
    if (text.is_open()){
        getline(text, line);
    }
    int chislo = 0, nach = 0;
    int razr = 0;
    for (int i = 0; i < line.length(); i++){
        if (chislo > 0 and !isNumber(line[i + razr])){
            string vstavka = toDvoich(chislo);
            line = slice(line, 0, nach) + vstavka + slice(line, nach + chisloRazr(chislo), line.length());
            razr += vstavka.length();
            chislo = 0;
        }
        if (isNumber(line[i + razr])){
            if (chislo == 0){
                nach = i + razr;
            }
            chislo = chislo * 10 + ctoi(line[i + razr]);
        }
    }
    ofstream out("hello'.txt");
    out << line;
}