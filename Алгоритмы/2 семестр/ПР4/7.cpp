#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int k, t, n;
    cout << "Введите сначала количество курьеров, а затем через пробел максимальную листанцию доставки: ";
    cin >> k >> t;
    cout << "Введите количество заказов, а затем в отдельных строках сколько нужно километров на их доставку: ";
    cin >> n;
    vector<int> deliveries;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        deliveries.push_back(x);
    }
    sort(deliveries.begin(), deliveries.end());
    reverse(deliveries.begin(), deliveries.end());
    int zad = 0;
    vector<int> temp;
    temp = deliveries;
    while (k > 0 and deliveries.size() > 0){
        int ost = t;
        int deleted = 0;
        for (int i = 0; i < deliveries.size(); i++){
            if (ost - deliveries[i] >= 0){
                ost -= deliveries[i];
                temp.erase(temp.begin() + i - deleted);
                deleted++;
            }
        }
        deliveries = temp;
        zad++;
        k--;
    }
    cout << zad << endl;
}