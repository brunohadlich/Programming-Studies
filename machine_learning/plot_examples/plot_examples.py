import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from math import sqrt, exp, log
from time import sleep, time
import csv


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


def plot_linear_regression_progress():
    x, y = load_dataset("ex1data2.txt")
    x, x_feature_mean, x_feature_standard_deviation = feature_normalize(x)
    m = len(x)
    x = [[1] + x[i] for i in range(m)]
    iterations = 400
    alpha = 0.1
    convergence_threshold = 0.0001
    theta, history_cost_iteration = gradient_descent(x, y, iterations, alpha, convergence_threshold)
    plot_gradient_descent(x, y, [(10000, 0.1), (10000, 0.01), (27000, 0.001)])


def inpute_age(cols):
    Age = cols[0]
    Pclass = cols[1]

    if pd.isnull(Age):

        if Pclass == 1:
            return 37
        elif Pclass == 2:
            return 29
        else:
            return 24
    else:
        return Age

def plot_dataset_info(train):
    sns.heatmap(train.isnull(),yticklabels=False,cbar=False,cmap='viridis')
    plt.show()
    sns.set_style('whitegrid')
    sns.countplot(x='Survived',data=train,palette='RdBu_r')
    plt.show()
    sns.set_style('whitegrid')
    sns.countplot(x='Survived',hue='Sex',data=train,palette='RdBu_r')
    plt.show()
    plt.figure(figsize=(12, 7))
    sns.boxplot(x='Pclass',y='Age',data=train,palette='winter')
    plt.show()
    train['Age'] = train[['Age','Pclass']].apply(inpute_age,axis=1)
    sns.heatmap(train.isnull(),yticklabels=False,cbar=False,cmap='viridis')
    plt.show()
    train.drop('Cabin',axis=1,inplace=True)
    train.dropna(inplace=True)
    sex = pd.get_dummies(train['Sex'],drop_first=True)
    embark = pd.get_dummies(train['Embarked'],drop_first=True)
    train.drop(['Sex','Embarked','Name','Ticket'],axis=1,inplace=True)
    train = pd.concat([train,sex,embark],axis=1)
    return train


if __name__ == "__main__":
    train = pd.read_csv("titanic_problem/train.csv")
    plot_dataset_info(train)
    plot_linear_regression_progress()
