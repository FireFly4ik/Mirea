#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string vvod;
    cin >> vvod;
    bool cms = false;
    for (int i = 0; i < vvod.length(); i++) {
        if (vvod[i] == ':') {
            cms = true;
            break;
        }
    }
    if (cms) {
        string Sch = vvod.substr(0, 2), Sm = vvod.substr(3, 2), Ssec = vvod.substr(6, 2);
        cout << stoi(Sch) * 3600 + stoi(Sm) * 60 + stoi(Ssec) << endl;
    } else {
        int ch, m, sec;
        int seconds = stoi(vvod);
        sec = seconds % 60;
        m = seconds / 60 % 60;
        ch = seconds / 3600;
        string Sch, Sm, Ssec;
        if (sec / 10 == 0) {
            Ssec = "0";
        }
        Ssec += to_string(sec);
        if (m / 10 == 0) {
            Sm = "0";
        }
        Sm += to_string(m);
        if (ch / 10 == 0) {
            Sch = "0";
        }
        Sch += to_string(ch);
        cout << Sch << ":" << Sm << ":" << Ssec << endl;
    }
    return 0;
}