#Uses python3

import sys

def format_cost(adj, cost):
	cost_ret = []
	for a in range(0, len(adj)):
		cost_ret.append({})
		for x in range(0, len(adj[a])):
			cost_ret[a][adj[a][x]] = cost[a][x]
	return cost_ret

def shortet_paths(adj, cost, s, distance, reachable, shortest):
	distance[s] = 0
	reachable[s] = 1
	for u in range(0, len(adj)):
		for u in range(0, len(adj)):
			for v in adj[u]:
				w = cost[u][v]
				if distance[u] + w < distance[v]:
					distance[v] = distance[u] + w
					reachable[v] = 1

	for u in range(0, len(adj)):
		for v in adj[u]:
			w = cost[u][v]
			if distance[u] + w < distance[v]:
				shortest[v] = 0

	for u in range(0, len(adj)):
		if shortest[u] == 0:
			v = adj[u][0]
			while v != u:
				shortest[v] = 0
				v = adj[v][0]

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
    s = data[0]
    s -= 1
    distance = [10**19] * n
    reachable = [0] * n
    shortest = [1] * n
    shortet_paths(adj, format_cost(adj,cost), s, distance, reachable, shortest)
    for x in range(n):
        if reachable[x] == 0:
            print('*')
        elif shortest[x] == 0:
            print('-')
        else:
            print(distance[x])

