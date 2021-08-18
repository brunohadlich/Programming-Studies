def pb(x, a):
    n = len(a)
    i1 = 0
    i2 = n - 1
    while i1 <= i2:
        m = (i1 + i2) // 2
        if x < a[m]:
            i2 = m - 1
        elif x > a[m]:
            i1 = m + 1
        else :
            return m
    return -1

print(pb(3,[1,2,4,5,6,8,14,17,19]))
