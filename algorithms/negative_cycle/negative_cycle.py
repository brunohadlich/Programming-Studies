#Uses python3

import sys

def format_cost(adj, cost):
	cost_ret = []
	for a in range(0, len(adj)):
		cost_ret.append({})
		for x in range(0, len(adj[a])):
			cost_ret[a][adj[a][x]] = cost[a][x]
	return cost_ret

def negative_cycle(adj, cost):
	dist = []
	pred = []

	for i in range(0, len(adj)):
		dist.append(999999999)
		pred.append(-1)

	dist[0] = 0
	for u in range(0, len(adj)):
		for u in range(0, len(adj)):
			for v in adj[u]:
				w = cost[u][v]
				if dist[u] + w < dist[v]:
					dist[v] = dist[u] + w
					pred[v] = u

	for u in range(0, len(adj)):
		for v in adj[u]:
			w = cost[u][v]
			if dist[u] + w < dist[v]:
				return 1
	return 0

if __name__ == '__main__':
    input = sys.stdin.read()
    data = list(map(int, input.split()))
    n, m = data[0:2]
    data = data[2:]
    edges = list(zip(zip(data[0:(3 * m):3], data[1:(3 * m):3]), data[2:(3 * m):3]))
    data = data[3 * m:]
    adj = [[] for _ in range(n)]
    cost = [[] for _ in range(n)]
    for ((a, b), w) in edges:
        adj[a - 1].append(b - 1)
        cost[a - 1].append(w)
    print(negative_cycle(adj, format_cost(adj,cost)))
