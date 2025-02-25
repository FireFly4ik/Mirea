/*
    Я понял задачу так, что у нас плитка размером 1x1 и нам нужно вычислить количество различных вариантов
    положить эту плитку в нам прямоугольник. Это будет факториал площади.
*/

#include <iostream>
using namespace std;

long long fact(long x){
    if (x > 1){
        return fact(x - 1) * x;
    }
    return 1;
}

int main(){
    int n;
    cin >> n;
    cout << fact(2 * n);
    return 0;
}