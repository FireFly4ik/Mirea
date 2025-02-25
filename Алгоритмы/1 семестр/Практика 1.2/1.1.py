def binary_search(arr, x):
    l, r = 0, len(arr) - 1
    while l <= r:
        if x == arr[(r + l) // 2]: return (r + l) // 2
        elif x < arr[(r + l) // 2]: r = (l + r) // 2
        else: l = (r + l) // 2
        if r - l == 1: return r, arr[:r] + [x] + arr[r:]


a = [1, 2, 3, 5, 6, 7, 9]
print(binary_search(a, 7))
print(binary_search(a, 4))
print(binary_search(a, 8))