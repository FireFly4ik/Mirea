from random import choice
from sys import setrecursionlimit
setrecursionlimit(100000000)

def printmas(tr):
    global mas, vs
    print("----------------------------------")
    print(*tr)
    mas[0][1] = "s"
    for i in range(vs):
        print(*mas[i])
    #mas[0][1] = 1

def mademas():
    global mas
    mas = [["w" for j in range(dl)] for i in range(vs)]
    #mas[0][1] = 1
    mas[vs - 1][dl - 2] = "e"
    for i in range(1, vs - 1):
        for j in range(1, dl - 1):
            mas[i][j] = choice([0, "w"])
    mas[1][1] = 1

def solve(th, pr, tr):
    global mas
    #printmas(tr)
    if th in tr:
        return "f"
    tr += [th]
    near = [[th[0] - 1, th[1]], [th[0] + 1, th[1]], [th[0], th[1] + 1], [th[0], th[1] - 1]]
    near.remove(pr)
    #if [0, 1] in near: near.remove([0, 1])
    wallsNear = 0
    nearNotWall = []
    if mas[th[0]][th[1]] == 0 or mas[th[0]][th[1]] > len(tr):
        mas[th[0]][th[1]] = len(tr)
    for i in range(len(near)):
        if mas[near[i][0]][near[i][1]] == "e":
            return len(tr)
        elif type(mas[near[i][0]][near[i][1]]) == str:
            wallsNear += 1
        else:
            nearNotWall.append([near[i][0], near[i][1]])
    if wallsNear == 3:
        mas[th[0]][th[1]] = "f"
        return "f"
    next = []
    for i in range(len(nearNotWall)):
        next.append(solve([nearNotWall[i][0], nearNotWall[i][1]], th, tr))
    if all(x == "f" for x in next):
        mas[th[0]][th[1]] = "f"
        return "f"
    ans = [x for x in next if type(x) == int]
    return min(ans)


dl, vs = map(int, input("Введите длину и высоту лабиринта с окружающими стенами через пробел: ").split())
while True:
    mademas()
    printmas("Старт")
    ans = solve([1, 1], [0, 1], [])
    #printmas()
    if type(ans) == int:
        break


printmas("Конец")
print(ans)