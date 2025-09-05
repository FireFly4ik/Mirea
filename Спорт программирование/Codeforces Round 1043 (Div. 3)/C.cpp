#include <iostream>
#include <vector>
using namespace std;

int main(){
    int t;
    cin >> t;
    vector<long long> kolvo;
    int q = 1;
    for (int i = 0; i < 19; i++){
        kolvo.push_back(q);
        q *= 3;
    }
    vector<long long> answers;
    for (int i = 0; i < t; i++){
        vector<long long> used = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        long long chislo, maxOps;
        cin >> chislo >> maxOps;
        long long summa = chislo * 3;
        long long m = chislo, s3 = 0;
        while (m) { s3 += m % 3; m /= 3; }

        // while (maxOps - k >= 2 ) {
        //     bool flag = false;
        //     int maxStepen = 0;
        //     for (int j = 18; j >= 0; j--) {
        //         if (j == 0) {
        //             flag = true;
        //         }
        //         if (used[j] > 0) {
        //             maxStepen = j;
        //             break;
        //         }
        //     }
        //     if (flag) break;
        //     k += 2;
        //     summa += 3 * (maxStepen - 1) * (kolvo[maxStepen - 1] / 3);
        //     summa -= maxStepen * (kolvo[maxStepen] / 3);
        //     used[maxStepen - 1] += 3;
        //     used[maxStepen]--;
        // }

        // answers.push_back(summa);

        if (maxOps < s3) {
            answers.push_back(-1);
            continue;
        }
        if (maxOps >= chislo) {
            answers.push_back(summa);
            continue;
        }
        

        long long needMerges = ( (chislo - maxOps) + 1 ) / 2;
        long long extra = 0;

        vector<long long> cnt = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        cnt[0] = chislo;

        for(int x = 0; needMerges > 0 && x + 1 < cnt.size(); ++x){
            long long avail = cnt[x] / 3;
            long long take = min(avail, needMerges);
            if (take > 0) {
                cnt[x] -= 3LL * take;
                cnt[x + 1] += take;
                extra += take * kolvo[x];
                needMerges -= take;
            }
        }

        answers.push_back(summa + extra);
    }
    for (int i = 0; i < t; i++){
       cout << answers[i] << endl;
    }
    return 0;
}