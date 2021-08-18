#Uses python3
import sys

# Return the trie built from patterns
# in the form of a dictionary of dictionaries,
# e.g. {0:{'A':1,'T':2},1:{'C':3}}
# where the key of the external dictionary is
# the node ID (integer), and the internal dictionary
# contains all the trie edges outgoing from the corresponding
# node, and the keys are the letters on those edges, and the
# values are the node IDs to which these edges lead.

def build_trie(patterns):
	idx = 0
	tree = [idx, {}]
	for p in patterns:
		current_node = tree
		for c in p:
			if not c in current_node[1]:
				idx+=1
				current_node[1][c] = [idx, {}]
			current_node = current_node[1][c]
	return tree

def print_pre_order_from_to(tree):
	idx = tree[0]
	for k in tree[1]:
		print(str(idx) + '->' + str(tree[1][k][0]) + ':' + str(k))
		print_pre_order_from_to(tree[1][k])

if __name__ == '__main__':
	patterns = sys.stdin.read().split()[1:]
	tree = build_trie(patterns)
	print_pre_order_from_to(tree)