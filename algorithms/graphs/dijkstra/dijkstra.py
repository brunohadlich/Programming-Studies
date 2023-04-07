#Uses python3

import sys
from heapq import heappush, heappop

def format_cost(adj, cost):
	cost_ret = []
	for a in range(0, len(adj)):
		cost_ret.append({})
		for x in range(0, len(adj[a])):
			cost_ret[a][adj[a][x]] = cost[a][x]
	return cost_ret

def dijkstra(adj, cost, s, t):
	cost_s_all = []
	queue = []
	for a in range(0, len(adj)):
		heappush(cost_s_all, (999999999, a))
		queue.append(a)
	cost_s_all.remove((999999999, s))
	heappush(cost_s_all, (0, s))

	dist = [999999999] * len(adj)
	dist[s] = 0

	while(len(queue) > 0):
		u = heappop(cost_s_all)[1]
		while (not (u in queue)):
			u = heappop(cost_s_all)[1]
		queue.remove(u)

		for v in adj[u]:
			d = dist[u] + cost[u][v]
			if d < dist[v]:
				dist[v] = d
				heappush(cost_s_all, (d, v))

	return -1 if dist[t] == 999999999 else dist[t]

def distance(adj, cost, s, t):
	return dijkstra(adj, format_cost(adj, cost), s, t)

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
    s, t = data[0] - 1, data[1] - 1
    print(distance(adj, cost, s, t))
