import math

def f(x):
    return 3 * x - 14 + math.e ** x - math.e ** (x * -1)

l = 1; r = 3; k = 0
while abs(f(l)) > 0.001:
    l = l - (r - l) * f(l) / (f(r) - f(l))
    k += 1

print(l, f(l), k)