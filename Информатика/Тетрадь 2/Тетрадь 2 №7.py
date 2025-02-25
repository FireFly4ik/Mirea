a = int(input())
print(True if all(a % i != 0 for i in range(2, int(a ** 0.5 + 1))) else False)
