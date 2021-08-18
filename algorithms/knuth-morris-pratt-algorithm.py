def computePrefixFunction(S):
    len_S = len(S)
    s = [0] * len_S
    border = 0
    for i in range(1, len_S):
        while (border > 0) and (S[i] != S[border]):
            border = s[border - 1]
        if S[i] == S[border]:
            border = border + 1
        else:
            border = 0
        s[i] = border
    return s

def kmp(pattern, text):
    S = pattern + "$" + text
    len_pattern = len(pattern)
    s = computePrefixFunction(S)
    result = []
    for i in range(len_pattern + 1, len(S)):
        if s[i] == len_pattern:
            result.append(i - (2 * len_pattern))
    return result

if __name__ == "__main__":
    pattern = "ABC"
    genome = "BJSDADAABCQWEQWEABC"
    print(*kmp(pattern, genome))
