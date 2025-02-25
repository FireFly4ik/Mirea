#include <iostream>
using namespace std;

class Node{
public:
    Node(double newChislo){
        chislo = newChislo;
    }

    void newNode(double newChislo){
        if (nextNodeAlive == true){
            nextNode->newNode(newChislo);
        } else {
            nextNode = new Node(newChislo);
            nextNodeAlive = true;
        }
    }

    double get(){
        return chislo;
    }

    bool checkSorted(){
        if (nextNodeAlive == true){
            if (nextNode->checkSorted() == true){
                if (chislo - nextNode->get() >= 0){
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return true;
        }
    }

private:
    double chislo;
    bool nextNodeAlive = false;
    Node *nextNode;
};

int main(){
    int n;
    double x;
    cin >> n >> x;
    Node node(x);
    for (int i = 0; i < n - 1; i++){
        cin >> x;
        node.newNode(x);
    }
    cout << node.checkSorted() << endl;
    return 0;
}