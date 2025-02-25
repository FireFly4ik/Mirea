import math

def f(x):
    return 3 * x - 14 + math.e ** x - math.e ** (x * -1)

l = 1; r = 3; k = 0
while (f(r) - f(l) > 0.001):
    if f((l + r) / 2) * f(l) > 0: l = (l + r) / 2
    else: r = (l + r) / 2
    k += 1

print(l, f(l), k)