#include <iostream>
#include <map>
using namespace std;

map<char, int> count(string stroka){
    map<char, int> hash;
    for (int i = 0; i < stroka.length(); i++){
        if (hash.find(stroka[i]) != hash.end()){
            hash[stroka[i]]++;
        } else {
            hash[stroka[i]] = 1;
        }
    }
    return hash;
}

int main(){
    string stroka;
    getline(cin, stroka);
    map<char, int> hash = count(stroka);
    for (auto& [letter, povtoreniya] : hash){
        cout << letter << "\t" << povtoreniya << endl;
    }
    return 0;
}