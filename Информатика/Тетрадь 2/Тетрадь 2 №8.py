a = int(input())
n = int(input())
s = []
while a > 0:
   s = [a % n] + s
   a //= n
print(s)
