import math
x, y = map(float, input().split())
s = math.sin(x + y)
if s <= -0.5: print(math.atan(abs(x - y) ** (1 / 3) * (x * math.e ** y)))
elif -0.5 < s < 0.5: print(3 * math.log(abs(x * y), 3))
else: print(x ** 3 + y **1.5)
