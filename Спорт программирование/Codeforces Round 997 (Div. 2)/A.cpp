#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t, x, y, n, m, plusX, plusY;
    vector<int> answers;
    cin >> t;
    for (int i = 0; i < t; i++){
        plusX = plusY = 0;
        cin >> n >> m;
        if (n < 2){
            cin >> x >> y;
            answers.push_back(m * 4);
        } else {
            for (int j = 0; j < n; j++){
                cin >> x >> y;
                if (j == 0){continue;}
                plusX += x;
                plusY += y;
            }
            answers.push_back((2 * m + plusX + plusY) * 2);
        }
    }
    for (int i = 0; i < t; i++){
        cout << answers[i] << endl;
    }
    return 0;
}