n = int(input())
while n > 0:
    if n & 1 == 1 and n == 1: print("YES"); break
    elif n & 1 == 0: n >>= 1
    else: print("NO"); break