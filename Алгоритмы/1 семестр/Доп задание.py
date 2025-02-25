from random import choice
from sys import setrecursionlimit
setrecursionlimit(100000000)

def printmas():
    global mas, vs, hashMas
    print("----------------------------------")
    for i in range(vs):
        print(*mas[i], "          ", *hashMas[i])

def mademas():
    global mas
    global hashMas
    mas = [["w" for j in range(dl)] for i in range(vs)]
    hashMas = [[0 for j in range(dl)] for i in range(vs)]
    mas[0][1] = 1
    mas[vs - 1][dl - 2] = "e"
    for i in range(1, vs - 1):
        for j in range(1, dl - 1):
            mas[i][j] = choice([0, "w"])
    mas[1][1] = 1

def solve(th, pr):
    global mas, hashMas
    hashMas[th[0]][th[1]] += 1
    #printmas()
    near = [[th[0] - 1, th[1]], [th[0] + 1, th[1]], [th[0], th[1] + 1], [th[0], th[1] - 1]]
    near.remove(pr)
    if [0, 1] in near: near.remove([0, 1])
    wallsNear = 0
    nearNotWall = []
    """try:"""
    if mas[th[0]][th[1]] == "f" or mas[pr[0]][pr[1]] == "f":
        return "f"
    elif mas[th[0]][th[1]] == 0 or mas[th[0]][th[1]] > mas[pr[0]][pr[1]] + 1:
        mas[th[0]][th[1]] = mas[pr[0]][pr[1]] + 1
    """except TypeError:
        print(mas[th[0]][th[1]], mas[pr[0]][pr[1]])
        printmas()"""
    for i in range(len(near)):
        if mas[near[i][0]][near[i][1]] == "e":
            return mas[th[0]][th[1]]
        elif type(mas[near[i][0]][near[i][1]]) == str:
            wallsNear += 1
        else:
            nearNotWall.append([near[i][0], near[i][1]])
    if wallsNear == 3:
        mas[th[0]][th[1]] = "f"
        return "f"
    if hashMas[th[0]][th[1]] > len(nearNotWall):
        return "f"
    next = []
    for i in range(len(nearNotWall)):
        next.append(solve([nearNotWall[i][0], nearNotWall[i][1]], th))
    if all(x == "f" for x in next):
        mas[th[0]][th[1]] = "f"
        return "f"
    ans = [x for x in next if type(x) == int]
    return min(ans)

print("Введите длину и высоту массива с окружающими стенами через пробел")
dl, vs = map(int, input().split())
while True:
    mademas()
    printmas()
    ans = solve([1, 1], [0, 1])
    #printmas()
    if type(ans) == int:
        break
printmas()
print(ans)