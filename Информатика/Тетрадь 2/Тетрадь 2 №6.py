a = int(input())
k = 1
sumWithWhile = 0
while k <= a:
   sumWithWhile += k
   k += 1
sumWithout = a * (a // 2 + 1) if a % 2 == 1 else (a + 1) * a // 2
print(sumWithWhile, sumWithout)