#include <iostream>
#include <set>
#include <string>
#include <cstring>
using namespace std;

int main(){
    string line;
    getline(cin, line);
    string temp;
    set<char> znaki = {',', '.', '-', '+', '-', '=', '_', ':', ';', '/', '?', '!', '(', ')'};
    set<string> words;
    for (int i = 0; i < line.length(); i++){
        if (znaki.count(line[i]) or line[i] == ' '){
            words.emplace(temp);
            temp = "";
        } else {
            char letter = tolower(line[i]);
            temp += letter;
        }
    }
    if (words.count("")){
        words.erase("");
    }
    return 0;
}