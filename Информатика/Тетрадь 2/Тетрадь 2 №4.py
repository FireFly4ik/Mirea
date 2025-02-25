a, b, c = map(int, input().split())
d = b ** 2 - 4 * a * c
if d > 0:
    print((-1 * b - d ** 0.5) / 2 / a, (-1 * b + d ** 0.5) / 2 / a)
elif d == 0:
    print(-1 * b / 2 / a)
else: print("Корней нет")