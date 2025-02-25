def f(arr):
    hashArr = [0] * (len(arr) - 1)
    for i in range(len(arr) - 2, -1, -1):
        for j in range(i, len(hashArr)):
            if arr[j] > arr[j + 1]:
                if j + 1 == len(arr) - 1:
                    hashArr[i] = 1
                    break
                hashArr[i] += hashArr[j + 1] + 1
                break
    return hashArr + [0]

print(f([5,2,6,1,0,9]))
print(f([5,2,6,1]))
print(f([0,1,2,3]))