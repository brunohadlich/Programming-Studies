def sortCharacters(s, alphabet_size):
    len_s = len(s)
    order = [0] * len_s
    count = [0] * alphabet_size
    for i in range(0, len_s):
        count[ord(s[i])] = count[ord(s[i])] + 1
    for j in range(1, alphabet_size):
        count[j] = count[j] + count[j - 1]
    for i in range(len_s - 1, -1, -1):
        c = s[i]
        count[ord(c)] = count[ord(c)] - 1
        order[count[ord(c)]] = i
    return order

def computeCharClasses(s, order):
    len_s = len(s)
    class_ = [0] * len_s
    class_[order[0]] = 0
    for i in range(1, len_s):
        if s[order[i]] != s[order[i - 1]]:
            class_[order[i]] = class_[order[i - 1]] + 1
        else:
            class_[order[i]] = class_[order[i - 1]]
    return class_

def sortDouble(s, l, order, class_):
    len_s = len(s)
    count = [0] * len_s
    newOrder = [0] * len_s
    for i in range(0, len_s):
        count[class_[i]] = count[class_[i]] + 1
    for j in range(1, len_s):
        count[j] = count[j] + count[j - 1]
    for i in range(len_s - 1, -1, -1):
        start = (order[i] - l + len_s) % len_s
        cl = class_[start]
        count[cl] = count[cl] - 1
        newOrder[count[cl]] = start
    return newOrder

def updateClasses(newOrder, class_, l):
    n = len(newOrder)
    newClass = [0] * n
    newClass[newOrder[0]] = 0
    for i in range(1 , n):
        cur = newOrder[i]
        prev = newOrder[i - 1]
        mid = (cur + l)
        midPrev = (prev + l) % n
        if (class_[cur] != class_[prev]) or (class_[mid] != class_[midPrev]):
            newClass[cur] = newClass[prev] + 1
        else:
            newClass[cur] = newClass[prev]
    return newClass

def buildSuffixArray(s):
    order = sortCharacters(s, 256)
    class_ = computeCharClasses(s, order)
    l = 1
    while l < len(s):
        order = sortDouble(s, l, order, class_)
        class_ = updateClasses(order, class_, l)
        l = 2 * l
    return order

if __name__ == "__main__":
    s = input()
    print(*buildSuffixArray(s))
