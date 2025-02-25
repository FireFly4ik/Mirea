// #include <iostream>
// #include <map>
// using namespace std;

// int main(){
//     int target;
//     cout << "Введите сумму, которая должна получиться: ";
//     cin >> target;
//     vector<map<int, vector<int>>> hash(target);
//     cout << "Введите сколько чисел будет занесено в таблицу: ";
//     int loops;
//     cin >> loops;
//     for (int i = 0; i < loops; i++){
//         int chislo;
//         cout << "Введите число: ";
//         cin >> chislo;
//         hash[abs(chislo) % target][chislo].push_back(i);
//     }
//     for (int i = 0; i < target;i++){
//         for (const auto& [ch, ind] : hash[i]){
//             if (hash[(ch >= 0 ? abs(target - i) : abs(i)) % target].count(target - ch)){
//                 if (target - ch != ch or (target - ch == ch and ind.size() > 1)){
//                     cout << ind[0] << " " << hash[(ch >= 0 ? abs(target - i) : abs(i)) % target][target - ch][hash[(ch >= 0 ? abs(target - i) : abs(i)) % target][target - ch].size() - 1] << " " << ch << "+" << target - ch << "=" << target << endl;
//                     return 0;
//                 }
//             } 
//         }
//     }
//     return 0;
// }