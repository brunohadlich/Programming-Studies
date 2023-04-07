#Uses python3

import sys

def distance(adj, s, t):
	parent = [-1] * len(adj)
	visited = [False] * len(adj)
	visited[s] = True
	queue = [s]
	while (len(queue) > 0):
		v = queue.pop(0)
		for w in adj[v]:
			if visited[w] == False:
				parent[w] = v
				visited[w] = True
				queue.append(w)
	if parent[t] != -1:
		paths = 0
		while parent[t] != -1:
			paths += 1
			t = parent[t]
		return paths
	if visited[t]:
		return 0
	return -1

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(data[0:(2 * m):2], data[1:(2 * m):2]))
    adj = [[] for _ in range(n)]
    for (a, b) in edges:
        adj[a - 1].append(b - 1)
        adj[b - 1].append(a - 1)
    s, t = data[2 * m] - 1, data[2 * m + 1] - 1
    print(distance(adj, s, t))
