#suffix array
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
#suffix array

#lcp
def lcpOfSuffixes(s, i, j, equal):
    lcp = max(0, equal)
    len_s = len(s)
    while i + lcp < len_s and j + lcp < len_s:
        if s[i + lcp] == s[j + lcp]:
            lcp = lcp + 1
        else:
            break
    return lcp

def invertSuffixArray(order):
    len_order = len(order)
    pos = [0] * len_order
    for i in range(0, len_order):
        pos[order[i]] = i
    return pos

def computeLCPArray(s, order):
    len_s = len(s)
    lcpArray = [0] * (len_s -1)
    lcp = 0
    posInOrder = invertSuffixArray(order)
    suffix = order[0]
    for i in range(0, len_s):
        orderIndex = posInOrder[suffix]
        if orderIndex == len_s - 1:
            lcp = 0
            suffix = (suffix + 1) % len_s
            continue
        nextSuffix = order[orderIndex + 1]
        lcp = lcpOfSuffixes(s, suffix, nextSuffix, lcp - 1)
        lcpArray[orderIndex] = lcp
        suffix = (suffix + 1) % len_s
    return lcpArray
#lcp

#suffix tree
class SuffixTreeNode:
    def __init__(self, children, parent, stringDepth, edgeStart, edgeEnd):
        self.children = children
        self.parent = parent
        self.stringDepth = stringDepth
        self.edgeStart = edgeStart
        self.edgeEnd = edgeEnd

def createNewLeaf(node, s, suffix):
    len_s = len(s)
    leaf = SuffixTreeNode({}, node, len_s - suffix, suffix + node.stringDepth, len_s - 1)
    node.children[s[leaf.edgeStart]] = leaf
    return leaf

def breakEdge(node, s, start, offset):
    startChar = s[start]
    midChar = s[start + offset]
    midNode = SuffixTreeNode({}, node, node.stringDepth + offset, start, start + offset - 1)
    midNode.children[midChar] = node.children[startChar]
    node.children[startChar].parent = midNode
    node.children[startChar].edgeStart = node.children[startChar].edgeStart + offset
    node.children[startChar] = midNode
    return midNode

def stFromSa(s, order, lcpArray):
    root = SuffixTreeNode({}, None, 0, -1, -1)
    lcpPrev = 0
    curNode = root
    len_s = len(s)
    for i in range(0, len_s):
        suffix = order[i]
        while curNode.stringDepth > lcpPrev and curNode.parent:
            curNode = curNode.parent
        if curNode.stringDepth == lcpPrev:
            curNode = createNewLeaf(curNode, s, suffix)
        else:
            edgeStart = order[i - 1] + curNode.stringDepth
            offset = lcpPrev - curNode.stringDepth
            midNode = breakEdge(curNode, s, edgeStart, offset)
            curNode = createNewLeaf(midNode, s, suffix)
        if i < len_s - 1:
            lcpPrev = lcpArray[i]
    return root
#suffix tree

def traverse(node, level):
    for c in node.children:
        print("char: ", c, ", level: ", level, ", stringDepth: ", node.stringDepth, ", edgeStart: ", node.edgeStart, ", edgeEnd: ", node.edgeEnd)
        traverse(node.children[c], level + 1)

if __name__ == "__main__":
    s = input()
    order = buildSuffixArray(s)
    lcpArray = computeLCPArray(s, order)
    tree = stFromSa(s, order, lcpArray)
    print(*order)
    print(*lcpArray)
    traverse(tree, 0)
