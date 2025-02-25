def binar(arr):
    l, r = 0, len(arr) - 1
    while l < r:
        q = (r + l) // 2
        if arr[q - 1] < arr[q] < arr[q + 1]:
            if r - l != 1:  l = q
            else: return "Массив не горный"
        elif arr[q - 1] > arr[q] > arr[q + 1]: r = q
        elif q != 0 and q != len(arr) - 1 and (arr[q - 1] < arr[q] > arr[q + 1]):
            return q
        else:
            return "Массив не горный"

print(binar([-1,0,1,2,3,4,5,4,3,2]))
print(binar([-100, -1, 19, 0, -1000, -5000]))
print(binar([4, 0, -5, -8, -1000]))
print(binar([-1204902, -12456, -123, 0, 6]))