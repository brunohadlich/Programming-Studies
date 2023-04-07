#Uses python3

import sys

def bipartite(adj):
	color = [-1] * len(adj)
	color[0] = 0
	queue = []

	for i in range(0, len(adj)):
		queue.append(i)

	while (len(queue) > 0):
		v = queue.pop(0)
		for w in adj[v]:
			if color[w] == -1:
				color[w] = 1 - color[v]
			else:
				if color[v] == -1:
					color[v] = 1 - color[w]
				else:
					if color[v] == color[w]:
						return 0
	return 1

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
    print(bipartite(adj))
