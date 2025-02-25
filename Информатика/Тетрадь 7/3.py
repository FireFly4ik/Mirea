def f(x):
    return x == x[::-1]

print(f("abba"))
print(f("abbb"))