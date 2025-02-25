#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Tree {
    void createTree(int left, int right) {
        startElement = left;
        length = pow(2, ceil(log2(right - left + 1)) + 1);
        drevo = vector<int>(length);
        int k = length / 2;
        for (int i = left; i <= right; i++){
            drevo[k] = i;
            k++;
        }
        for (int i = length / 2 - 1; i > -1; i--){
            drevo[i] = drevo[i * 2] + drevo[i * 2 + 1];
        }
        return;
    }

    void minOnLine(int left, int right){
        cout << left << endl;
        return;
    }

    void maxOnLine(int left, int right){
        cout << right - 1 << endl;
        return;
    }

    void oddEven(int left, int right, bool even){
        if ((right - left) % 2 == 0){
            cout << (right - left) / 2 << endl;
            return;
        }
        if ((right - 1) % 2 == 1){
            cout << (right - left) / 2 + !even << endl;
        } else {
            cout << (right - left) / 2 + even << endl;
        }
        return;
    }

    void sumDrevo(int leftBorder, int rightBorder){
        int k = 0;
        int left = leftBorder - startElement + length / 2;
        int right = rightBorder - startElement + length / 2 - 1;
        
        while (left <= right){
            if (left % 2 != 0){
                k += drevo[left];
            }
            if (right % 2 == 0){
                k += drevo[right];
            }
            right = (right - 1) / 2;
            left = (left + 1) / 2;
        }
        cout << k << endl;
        return;
    }

    vector<int> drevo;
    int length, startElement;
};

int main(){
    Tree* tree = new Tree;
    tree->createTree(87, 119);
    tree->sumDrevo(87, 89);
    tree->oddEven(87, 119, 1);
    tree->minOnLine(87,119);
    tree->maxOnLine(87, 119);
    delete(tree);
    return 0;
}