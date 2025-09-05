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
        for (auto x : children){
            summ += x.second->length();
        }
        return summ + isEnd;
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
};

int main(){
    Tree* tree = new Tree;
    tree->insert("q");
    tree->insert("qa");
    tree->insert("qs");
    tree->insert("qd");
    cout << tree->lengthWithPref("") << endl;
    cout << tree->lengthWithPref("q") << endl;
    cout << tree->lengthWithPref("qa") << endl;
    cout << tree->lengthWithPref("w") << endl;
    tree->deleteTree();
    return 0;
}