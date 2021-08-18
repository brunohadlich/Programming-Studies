import csv
from math import sqrt, exp


def load_dataset(f_name):
    x = []
    y = []
    with open(f_name, mode="r") as f:
        while True:
            line = f.readline()
            if not line:
                break
            splitted = list(map(float, line.strip().split(",")))
            x.append(splitted[:-1])
            y.append(splitted[-1:])
    return (x, y)


def sigmoid(x):
    m = len(x)
    return [1 / (1 + exp(-z)) for z in x]


def hypothesis(theta, x):
    """
    >>> hypothesis([3, 4, 5], [1, 3, 4])
    35
    >>> hypothesis([7, 2, 9, 1], [1, 7, 1, 8])
    38
    >>> hypothesis([13, 7, 3, 2], [1, 10, 32, 7])
    193
    """
    return sum([theta[i] * x[i] for i in range(len(theta))])


def cost_function(theta, x, y):
    m = len(x)
    return (1 / (2 * m)) * sum([pow(hypothesis(theta, x[i]) - y[i][0], 2) for i in range(m)])


def gradient_descent(x, y, max_iterations=1000, alpha=0.01, convergence_threshold=0.0001):
    n_iterations = 0
    convergence = 999999
    m = len(x)
    n = len(x[0])
    theta = [0] * n
    last_cost = cost_function(theta, x, y)
    history_cost_iteration = []
    while convergence > convergence_threshold and n_iterations < max_iterations:
        for j in range(n):
            theta[j] -= alpha * (1 / m) * sum([(hypothesis(theta, x[i]) - y[i][0]) * x[i][j] for i in range(m)])
        c = cost_function(theta, x, y)
        convergence = abs(last_cost - c)
        last_cost = c
        n_iterations += 1
        history_cost_iteration.append(c)
    return (theta, history_cost_iteration)


def mean(x):
    m = len(x)
    n = len(x[0])
    x_feature_mean = [0] * n
    for i in range(n):
        x_feature_mean[i] = sum([x[k][i] for k in range(m)]) / m
    return x_feature_mean


def standard_deviation(x):
    m = len(x)
    n = len(x[0])
    x_feature_mean = mean(x)
    x_feature_standard_deviation = [0] * n
    for i in range(n):
        x_feature_standard_deviation[i] = sqrt(1 / (m - 1) * sum([pow(x[k][i] - x_feature_mean[i], 2) for k in range(m)]))
    return x_feature_standard_deviation


def feature_normalize(x):
    m = len(x)
    n = len(x[0])
    x_feature_mean = mean(x)
    x_feature_standard_deviation = standard_deviation(x)
    for i in range(n):
        for k in range(m):
            x[k][i] -= x_feature_mean[i]
            x[k][i] /= x_feature_standard_deviation[i]
    return (x, x_feature_mean, x_feature_standard_deviation)

def plot_gradient_descent(x, y, iterations_alpha):
    import matplotlib.pyplot as plt
    import pandas as pd
    max_iterations = 0

    for iteration_alpha in iterations_alpha:
        max_iterations = max(iteration_alpha[0], max_iterations)

    values = {'x': [i for i in range(1, max_iterations + 1)]}
    idx_test = 0
    iterations_count = {}
    for a in iterations_alpha:
        iterations_count[a[1]] = []
    for iteration_alpha in iterations_alpha:
        idx_test += 1
        iterations = iteration_alpha[0]
        alpha = iteration_alpha[1]
        theta, history_cost_iteration = gradient_descent(x, y, iterations, alpha)
        iterations = len(history_cost_iteration)
        history_cost_iteration = history_cost_iteration + [0 for i in range(max_iterations - iterations)]
        if not (iterations in iterations_count[alpha]):
            name = 'alpha {} iterations {}'.format(alpha, iterations)
            values[name] = history_cost_iteration
            df=pd.DataFrame(values)
            plt.plot( 'x', name, data=df)
            iterations_count[alpha].append(iterations)

    plt.legend()
    plt.xlabel("iterations")
    plt.ylabel("cost")
    plt.title("Cost decreases as the number of iterations increase")
    plt.show()

def test_linear_regression(x, x_feature_mean, x_feature_standard_deviation, theta):
    test = [[1650, 3]]
    for i in range(len(test)):
        test[i] = [(test[i][k] - x_feature_mean[k]) / x_feature_standard_deviation[k] for k in range(len(test[i]))]
    test = [[1] + test[i] for i in range(len(test))]
    print("Using theta equals to {}, a test with entry {} results in a hypothesis {}.\n".format(theta, test[0], hypothesis(theta, test[0])))

if __name__ == "__main__":
    x, y = load_dataset("ex1data2.txt")
    x, x_feature_mean, x_feature_standard_deviation = feature_normalize(x)
    m = len(x)
    x = [[1] + x[i] for i in range(m)]
    iterations = 400
    alpha = 0.1
    convergence_threshold = 0.0001
    theta, history_cost_iteration = gradient_descent(x, y, iterations, alpha, convergence_threshold)
    print("\nNumber of samples: {}.\n".format(m))
    print("Theta is equal to {} after {} gradient descent iterations using alpha equals to {} and convergence threshold of {} reaching a cost of {}.\n".format(theta, iterations, alpha, convergence_threshold, cost_function(theta, x, y)))
    test_linear_regression(x, x_feature_mean, x_feature_standard_deviation, theta)
    #plot_gradient_descent(x, y, [(10000, 0.1), (10000, 0.01), (27000, 0.001)])
