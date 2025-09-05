#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

int main()
{
    ll n;
    cin >> n;
    vector<ll> total;
    ll maxi = 0;
    ll ind = 0;
    for (ll i = 0; i < n; i++)
    {
        int a, b, k;
        cin >> a >> b >> k;
        if (total.size() < b + b - a){
            for (int j = total.size(); j <= (b > 1000000000 ?1000000000 : b + b - a); j++){
                total.push_back(0);
            }
        }
        for (ll j = a; j <= (b > 1000000000 ?1000000000 : b + b - a); j++){
            if (j > b){
                total[j] = (total[j - 1] - k);
                if (total[j] > maxi){
                    maxi = total[j];
                    ind = j;
                }
            } else {
                total[j] = (total[j - 1] + k);
                if (total[j] > maxi){
                    maxi = total[j];
                    ind = j;
                }
            }
        }
    }
    cout << ind << endl;
    return 0;
}