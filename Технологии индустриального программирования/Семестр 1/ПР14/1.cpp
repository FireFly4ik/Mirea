#include <iostream>
#include <stack>
using namespace std;

int main(){
    string line;
    stack<char> st;
    bool flag = true;
    getline(cin, line);
    for (int i = 0; i < line.length(); i++){
        if (line[i] == '('){
            st.push(line[i]);
        } else if (line[i] == ')' and st.size() < 1){
            flag = false;
            break;
        } else if (line[i] == ')'){
            st.pop();
        }
    }
    if (st.size() != 0){
        flag = false;
    }
    cout << flag << endl;
}