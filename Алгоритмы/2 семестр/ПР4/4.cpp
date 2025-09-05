#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
    string letter;
    Node* left;
    Node* right;
    float rate;
};

struct Tree {
    Node* root;

    map<string, string> code;

    vector<pair<string, float>> makeRates(string stroka) {
        map<char, int> letters;
        for (char c : stroka) {
            letters[c]++;
        }
        vector<pair<string, float>> rates;
        for (auto x : letters) {
            string s(1, x.first);
            rates.push_back({s, float(x.second) / stroka.length()});
        }
        sort(rates.begin(), rates.end(), [](const pair<string, float>& a, const pair<string, float>& b) {
            return a.second < b.second;
        });
        return rates;
    }

    void generateCodes(Node* node, string currentCode = "") {
        if (!node) return;
        if (node->letter.length() == 1) {
            code[node->letter] = currentCode;
            return;
        }
        generateCodes(node->left, currentCode + "0");
        generateCodes(node->right, currentCode + "1");
    }

    void printCodes() {
        for (const auto& pair : code) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    void createTree(string word) {
        vector<pair<string, float>> rates = makeRates(word);
        vector<pair<float, Node*>> nodes;
        for (const auto& rate : rates) {
            Node* node = new Node{rate.first, nullptr, nullptr, rate.second};
            nodes.push_back({rate.second, node});
        }
        while (nodes.size() > 1) {
            Node* left = nodes[0].second;
            Node* right = nodes[1].second;
            Node* parent = new Node;
            parent->left = left;
            parent->right = right;
            parent->letter = left->letter + right->letter;
            parent->rate = left->rate + right->rate;
            nodes.push_back({parent->rate, parent});
            nodes.erase(nodes.begin(), nodes.begin() + 2);
            sort(nodes.begin(), nodes.end(), [](const pair<float, Node*>& a, const pair<float, Node*>& b) {
                return a.first < b.first;
            });
        } 
        root = nodes.back().second;
        generateCodes(root);
    }

    string encode(string word) {
        string encoded;
        for (char c : word) {
            encoded += code[string(1, c)];
        }
        return encoded;
    }

    float koef(string word){
        string encoded = encode(word);
        return float(word.length() * 8) / float(encoded.length());
    }

    string decode(string encoded){
        string decoded = "";
        string last = "";
        for (int i = 0; i < encoded.length(); ++i){
            last += encoded[i];
            for (const auto& pair : code) {
                if (pair.second == last) {
                    decoded += pair.first;
                    last = "";
                    break;
                }
            }
        }
        return decoded;
    }

    void print(Node* node, int space = 0){
        if (!node) return;
        space += 2;
        print(node->right, space);
        for (int i = 2; i < space; ++i){
            cout << " ";
        }
        cout << node->letter << "(" << (node->rate) << ")" << endl;
        print(node->left, space);
    }
};

int main() {
    Tree* tree = new Tree;
    tree->createTree("mama_mila_ramu");
    tree->print(tree->root);
    tree->printCodes();
    cout << tree->encode("mama_mila_ramu") << endl;
    cout << "Коэффициент сжатия: " << tree->koef("mama_mila_ramu") << endl;
    cout << "Декодирование: " << tree->decode(tree->encode("mama_mila_ramu")) << endl;
    delete tree;
    return 0;
}