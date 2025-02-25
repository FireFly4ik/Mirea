#include <stack>
#include <iostream>
#include <string>
using namespace std;

int main(){
    string a;
    cin >> a;
    stack <char> st;
    for (int i = 0; i < a.length(); i++){
        st.push(a[i]);
    }
    string b;
    int q = st.size();
    for (int i = 0; i < q; i++){
        char tempChar = st.top();
        b += tempChar;
        st.pop();
    }
    cout << b << endl;
    return 0;
}