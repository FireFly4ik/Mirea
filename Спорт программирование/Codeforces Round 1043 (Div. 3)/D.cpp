#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n, m, q;
        cin >> n >> m >> q;
        vector<long long> vadim(n), kostya(m);
        for (int i = 0; i < n; i++) cin >> vadim[i];
        for (int i = 0; i < m; i++) cin >> kostya[i];

        sort(vadim.rbegin(), vadim.rend());
        sort(kostya.rbegin(), kostya.rend());

        vector<long long> prefA(n+1,0), prefB(m+1,0);
        for(int i=0;i<n;i++) prefA[i+1]=prefA[i]+vadim[i];
        for(int i=0;i<m;i++) prefB[i+1]=prefB[i]+kostya[i];

        while(q--){
            int x,y,z;
            cin >> x >> y >> z;
            long long ans=0;
            for(int i=0;i<=min(x,z);i++){
                int j=z-i;
                if(j<=y){
                    ans=max(ans, prefA[i]+prefB[j]);
                }
            }
            cout << ans << "\n";
        }
    }
}