import math

def f(x):
    return 3 * x - 14 + math.e ** x - math.e ** (x * -1)

def kas(x):
    return 3 + + math.e ** x + 1 / math.e ** x

l = 1; r = 3; k = 0
while abs(f(r)) > 0.001:
    r = r - f(r) / kas(r)
    k += 1

print(r, f(r), k)