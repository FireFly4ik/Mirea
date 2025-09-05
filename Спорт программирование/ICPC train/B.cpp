#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int d, m, y, ans;
    cin >> d >> m >> y;
    if (y < 1700 || (y == 1700 && m <= 3 && d <= 11))
    {
        ans = 10;
    }
    else if (y < 1800 || (y == 1800 && m <= 3 && d <= 12))
    {
        ans = 11;
    }
    else if (y < 1900 || (y == 1900 && m <= 3 && d <= 13))
    {
        ans = 12;
    }
    else if (y < 2100 || (y == 2100 && m <= 3 && d <= 14))
    {
        ans = 13;
    }
    else if (y < 2200 || (y == 2200 && m <= 3 && d <= 15))
    {
        ans = 14;
    }
    else if (y < 2300 || (y == 2300 && m <= 3 && d <= 16))
    {
        ans = 15;
    }
    else if (y < 2500 || (y == 2500 && m <= 3 && d <= 18))
    {
        ans = 16;
    }

    cout << ans << endl;

    return 0;
}