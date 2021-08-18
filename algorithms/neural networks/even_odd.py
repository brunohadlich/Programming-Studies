from math import exp
from random import random

def multiply_vectors(v1, v2, v_dest=None):
	v_dest = v_dest if (v_dest != None) else [None] * len(v1)
	for i in range(len(v1)):
		v_dest[i] = v1[i] * v2[i]
	return v_dest

def sum_vectors(v1, v2, v_dest=None):
	v_dest = v_dest if (v_dest != None) else [None] * len(v1)
	for i in range(len(v1)):
		v_dest[i] = v1[i] + v2[i]
	return v_dest

def sum_scalars(v):
	total = 0
	for i in v:
		total += i
	return total

def calc_total_net_input(v_weight, v_input, bias):
	return sum_scalars(multiply_vectors(v_weight, v_input)) + bias * 1

def logistic_function(n):
	return 1 / (1 + exp(n))

class NeuralNetwork:
	#argument: an array, each element represents the number of neurons in the layer
	#of the index of the element like [4,3,2,6] this argument means that the first
	#layer or input layer will have 4 neurons, second layer 3 neurons, third layer
	#2 neurons and fourth layer or output layer 6 neurons.
	def __init__(self, neurons_per_layer):
		self.neurons_per_layer = neurons_per_layer
		self.weights = []
		for l in range(len(self.neurons_per_layer) - 1):
			idx_layer = 1 + l
			n_neurons = self.neurons_per_layer[idx_layer]
			self.weights.append([[]] * n_neurons)
			for n in range(n_neurons):
				self.weights[l][n] = [0] * self.neurons_per_layer[idx_layer - 1]
				for w in range(len(self.weights[l][n])):
					self.weights[l][n][w] = random()
nn = NeuralNetwork([4,3,2,6])

for x in nn.weights:
	print(x)
	for i in x:
		print(i)