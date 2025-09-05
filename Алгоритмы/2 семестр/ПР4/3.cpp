#include <iostream>
#include <map>
using namespace std;

struct Node {
    map<char, Node*> children;
    bool isEnd = false;

    bool isEmpty() {
        return children.empty();
    }

    void deleteNodes(){
        for (auto x : children){
            x.second->deleteNodes();
        }
        delete this;
    }

    int length() {
        int summ = 0;
        if (children.size() != 0){
            for (auto x : children){
                if (x.second != nullptr){
                    summ += x.second->length();
                }
            }
        }
        return summ + isEnd;
    }

    void deleteWord(string word, int ind){
        if (ind < word.length() and (isEmpty() or children.count(word[ind]) == 0)){
            cout << "Такого слова нет" << endl;
            return;
        }
        if (ind < word.length()){
            children[word[ind]]->deleteWord(word, ind + 1);
        }
        if (ind == word.length()) {
            isEnd = false;
        }
        if (!isEnd and (children.size() == 0 or !length())){
            delete this;
        }
    }
};

struct Tree {
    Node* root = new Node;

    void insert (string word) {
        Node* last = root;
        for (int i = 0; i < word.length(); i++){
            if (last->children.count(word[i]) == 0) {
                Node* newNode = new Node;
                last->children[word[i]] = newNode;
            }
            last = last->children[word[i]];
        }
        last->isEnd = true;
    }

    void deleteTree(){
        root->deleteNodes();
        delete this;
    }

    bool search(string word) {
        Node* last = root;
        for (int i = 0; i < word.length(); i++){
            if (last->children.count(word[i]) == 0) {
                return 0;
            }
            last = last->children[word[i]];
        }
        return last->isEnd;
    }

    string wordWithMorePrefixes (vector<string>* words){
        string maxWord;
        int maxPrefixes = 0;
        Node* last = root;
        for (auto word : (*words)){
            int prefixes = 0;
            last = root;
            for (int i = 0; i < word.length(); i++){
                if (last->children.count(word[i]) == 0) {
                    break;
                }
                if (last->isEnd) {
                    prefixes ++;
                }
                last = last->children[word[i]];
            }
            if (prefixes > maxPrefixes){
                maxPrefixes = prefixes;
                maxWord = word;
            }
        }
        return maxWord;
    }
};

int main(){
    Tree* tree = new Tree;
    int n;
    cin >> n;
    vector<string> mas;
    for (int i = 0; i < n; i++){
        string word;
        cin >> word;
        mas.push_back(word);
    }
    for (auto x : mas){
        tree->insert(x);
    }
    cout << tree->wordWithMorePrefixes(&mas) << endl;
    // tree->deleteTree();
    return 0;
}