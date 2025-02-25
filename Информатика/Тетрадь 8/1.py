word = str(input("Слово с четным колвом букв: "))
a = len(word)
b = a // 2
qu = []
for i in range(b):
    qu.append(word[0])
    word = word[1:]
qu.reverse()
for i in range(b):
    qu.append(word[0])
    word = word[1:]
print(*qu)