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

    int lengthWithPref(string pref){
        Node* last = root;
        for (int i = 0; i < pref.length(); i++){
            if (last->children.count(pref[i]) == 0) {
                return 0;
            }
            last = last->children[pref[i]];
        }
        return last->length();
    }

    void deleteWord(string word){
        root->deleteWord(word, 0);
    }
};

int main(){
    Tree* tree = new Tree;
    tree->insert("q");
    tree->insert("qa");
    tree->deleteWord("q");
    cout << tree->search("q") << endl;
    cout << tree->search("qa") << endl;
    tree->deleteWord("qa");
    cout << tree->search("qa") << endl;
    cout << tree->root->children.size() << endl;
    // tree->deleteTree();
    return 0;
}