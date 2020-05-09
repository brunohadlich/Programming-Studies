lista = [5,3,7,9,6,3,1,2,5,7,4,2,6,4,67,2,1]

def quicksort(l):
    if l:
        left = [x for x in l if x < l[0]]
        right = [x for x in l if x > l[0]]
        if len(left) > 1:
            left = quicksort(left)
        if len(right) > 1:
            right = quicksort(right)
        return left + [l[0]] * l.count(l[0]) + right
    return []
 
print(quicksort(lista))
