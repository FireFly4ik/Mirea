n = int(input())
A = str(input())
ans = 0
for i in range(len(A)):
    ans += (int(A[-1 - i]) * n ** i)
print(ans)