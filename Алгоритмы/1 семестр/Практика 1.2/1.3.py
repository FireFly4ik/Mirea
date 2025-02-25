def binar(arr):
    while 0 in arr: arr.remove(0)
    if len(arr) == 0: return 0
    l, r = 0, len(arr) - 1
    while l < r:
        q = (l + r) // 2
        if arr[q] < 0:
            if l == len(arr) - 2: return(len(arr))
            l = q
            if arr[q + 1] > 0: return max(q + 1, len(arr) - q - 1)
        elif arr[q] > 0:
            if r == 1: return len(arr)
            r = q
            if arr[q - 1] < 0: return max(q, len(arr) - q)

print(binar([-7,-7,-4,-3,-3,-2,-1, 0, 0, 6,7,8,9,9,9,9,10]))
print(binar([-7,-7,-4,-3,-3,-2,-1, 0, 0, 6,7,8,9,9,9,9]))
print(binar([-7,-7,-4,-3,-3,-2,-1, 0, 0, 6,7,8,9,9,9]))
print(binar([1,1,1,1,1]))
print(binar([-1,-1,-1]))
print(binar([-1, 4, 5]))
print(binar([0,0,0,0]))