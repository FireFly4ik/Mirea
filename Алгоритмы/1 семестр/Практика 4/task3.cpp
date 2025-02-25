/*import math

def f(x):
    return 3 * x - 14 + math.e ** x - math.e ** (x * -1)

l = 1; r = 3; k = 0
while (f(r) - f(l) > 0.001):
    if f((l + r) / 2) * f(l) > 0: l = (l + r) / 2
    else: r = (l + r) / 2
    k += 1

print(l, f(l), k)*/
#include <iostream>
#include <cmath>
using namespace std;

double f(double x){
    return 3 * x - 14 + pow(M_E, x) - pow(M_E, (-1 * x));
}

double recursia(double l, double r){
    if (f(r) - f(l) > 0.001){
        if (f((l + r) / 2) * f(l) > 0){
            return recursia((l + r) / 2, r);
        } else {
            return recursia(l, (l + r) / 2);
        }
    }
    return l;
}

int main(){
    double l = 1, r = 3;
    cout << recursia(l, r) << " " << f(recursia(l, r)) << endl;
    return 0;
}