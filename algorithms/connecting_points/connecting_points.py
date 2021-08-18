#Uses python3
import sys
from heapq import heappush, heappop, heapify
from math import pow, sqrt

def get_distance(x1, x2, y1, y2):
	return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2))

def most_depht(i, v):
	k = v[i]
	while k != i:
		pivot = k
		k = v[k]
		i = pivot
	return k

def same(x, y, v):
	return most_depht(x, v) == most_depht(y, v)

def all_same_set(v):
	for i in range(0, len(v) - 1):
		if (not same(i, i + 1, v)):
			return False
	return True

def minimum_distance(x, y):
	vertexes = [i for i in range(0, len(x))]

	sorted_edges = []

	for vertex_k in range(0, len(x) - 1):
		for vertex_j in range(vertex_k + 1, len(x)):
			heappush(sorted_edges, (get_distance(x[vertex_k], x[vertex_j], y[vertex_k], y[vertex_j]), vertex_k, vertex_j))

	result = 0

	while (not all_same_set(vertexes)):
		lightest_edge = heappop(sorted_edges)
		if (not same(lightest_edge[1], lightest_edge[2], vertexes)):
			most_depht_v1 = most_depht(lightest_edge[1], vertexes)
			most_depht_v2 = most_depht(lightest_edge[2], vertexes)
			vertexes[most_depht_v1] = vertexes[most_depht_v2] = min(most_depht_v1, most_depht_v2)
			result += lightest_edge[0]
	return result

if __name__ == '__main__':
	input = sys.stdin.read()
	data = list(map(int, input.split()))
	n = data[0]
	x = data[1::2]
	y = data[2::2]
	print("{0:.9f}".format(minimum_distance(x, y)))
