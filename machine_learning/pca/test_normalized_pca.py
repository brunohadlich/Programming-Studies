import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from warnings import simplefilter
import matplotlib.pyplot as plt
simplefilter(action='ignore', category=FutureWarning)
from scipy.ndimage.interpolation import rotate
import math
import statistics

np.random.seed(0)

def mean(X):
    return sum(X) / len(X)

def variance(X):
    m = mean(X)
    return sum([pow(x - m, 2) for x in X]) / (len(X) - 1)

def standard_deviation(X):
    return math.sqrt(variance(X))

def zscore_normalization(X):
    m = len(X)
    X_mean = mean(X)
    X_sdv = standard_deviation(X)
    for x in X:
        yield (x - X_mean) / X_sdv

def performance_with_n_components(X_train, X_test, y_train, y_test, n_components):
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)
    X_test = sc.transform(X_test)

    pca = PCA(n_components)
    X_train = pca.fit_transform(X_train)
    X_test = pca.transform(X_test)

    classifier = RandomForestClassifier(max_depth=20, random_state=0)
    classifier.fit(X_train, y_train)

    y_pred = classifier.predict(X_test)

    cm = confusion_matrix(y_test, y_pred)
    print(f"Precisão treinando com {n_components} componente(s): {accuracy_score(y_test, y_pred)*100}%")
    return accuracy_score(y_test, y_pred)*100


def get_components_to_achieve_variance(X_train, desired_variance):
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)

    pca = PCA()
    X_train = pca.fit_transform(X_train)

    explained_variance = pca.explained_variance_ratio_

    print(explained_variance)

    n_components = 0
    acumulated_variance = 0

    for idx, variance in enumerate(explained_variance):
        acumulated_variance += variance
        n_components += 1
        if acumulated_variance >= desired_variance:
            break
    return n_components

def rotateX(x, y, mu_x, mu_y, angle):
    return math.cos(angle) * (x - mu_x) - math.sin(angle) * (y - mu_y) + mu_x

def rotateY(x, y, mu_x, mu_y, angle):
    return math.sin(angle) * (x - mu_x) + math.cos(angle) * (y - mu_y) + mu_x

def get_class(x, y):
    return 1 if y <= (x - 3) else 2

def get_class2(x, y):
    return 1 if x >= 40 and y >= 40 else 2

def teste1():
    n = 150
    x1 = np.random.uniform(low=-15, high=60, size=(n,))
    x2 = np.random.uniform(low=-10, high=10, size=(n,))
    ar = [[xx1, xx2] for xx1, xx2 in zip(x1, x2)]
    m = np.array(ar, float)
    x1_mean = statistics.mean(x1)
    x2_mean = statistics.mean(x2)
    for i in range(n):
        m[i,0] += rotateX(m[i,0], m[i,1], x1_mean, x2_mean, 45)
        m[i,1] += rotateY(m[i,0], m[i,1], x1_mean, x2_mean, 45)
    result = [get_class(x, y) for x, y in zip(m[:,0], m[:,1])]
    plt.ylim(-20, 120)
    plt.xlim(-20, 120)
    for i in range(n):
        plt.plot(m[i,0], m[i,1], 'bo' if result[i] == 1 else 'ro')

    X_train = m
    y_train = result

    total_features = X_train.shape[1]
    print("========================\nTeste 1:\n")

    print(f"Dataset contém {X_train.shape[0]} registros e {total_features} features")

    X_train, X_test, y_train, y_test = train_test_split(X_train, y_train, test_size=0.3, random_state=0)

    print(f"Conjunto de trainamento contém {X_train.shape[0]} registros")
    print(f"Conjunto de testes contém {X_test.shape[0]} registros")

    acumulated_variance = 0.95
    n_components = get_components_to_achieve_variance(X_train, acumulated_variance)

    print(f"São necessários {n_components} componentes para atingir {acumulated_variance * 100}% de toda variância do conjunto de treinamento do dataset.")

    precisao = performance_with_n_components(X_train, X_test, y_train, y_test, 1)
    performance_with_n_components(X_train, X_test, y_train, y_test, 2)

    plt.title(f"Sem normalização z-score, precisão de {precisao}% usando 1 componente principal")

    plt.show()

def teste2():
    n = 150
    x1 = np.random.uniform(low=-15, high=60, size=(n,))
    x2 = np.random.uniform(low=-10, high=10, size=(n,))
    ar = [[xx1, xx2] for xx1, xx2 in zip(x1, x2)]
    m = np.array(ar, float)
    x1_mean = statistics.mean(x1)
    x2_mean = statistics.mean(x2)
    for i in range(n):
        m[i,0] += rotateX(m[i,0], m[i,1], x1_mean, x2_mean, 45)
        m[i,1] += rotateY(m[i,0], m[i,1], x1_mean, x2_mean, 45)
    result = [get_class(x, y) for x, y in zip(m[:,0], m[:,1])]

    x1 = [x for x in m[:,0]]
    x2 = [x for x in m[:,1]]
    x1 = list(zscore_normalization(x1))
    x2 = list(zscore_normalization(x2))
    ar = [[xx1, xx2] for xx1, xx2 in zip(x1, x2)]
    m = np.matrix(ar, float)

    for i in range(n):
        plt.plot(m[i,0], m[i,1], 'bo' if result[i] == 1 else 'ro')

    X_train = m
    y_train = result

    total_features = X_train.shape[1]
    print("========================\nTeste 2:\n")

    print(f"Dataset contém {X_train.shape[0]} registros e {total_features} features")

    X_train, X_test, y_train, y_test = train_test_split(X_train, y_train, test_size=0.3, random_state=0)

    print(f"Conjunto de trainamento contém {X_train.shape[0]} registros")
    print(f"Conjunto de testes contém {X_test.shape[0]} registros")

    acumulated_variance = 0.95
    n_components = get_components_to_achieve_variance(X_train, acumulated_variance)

    print(f"São necessários {n_components} componentes para atingir {acumulated_variance * 100}% de toda variância do conjunto de treinamento do dataset.")

    precisao = performance_with_n_components(X_train, X_test, y_train, y_test, 1)
    performance_with_n_components(X_train, X_test, y_train, y_test, 2)

    plt.title(f"Com normalização z-score, precisão de {precisao}% usando 1 componente principal")

    plt.show()

def teste3():
    n = 150
    x1 = np.random.uniform(low=-15, high=60, size=(n,))
    x2 = np.random.uniform(low=-10, high=10, size=(n,))
    ar = [[xx1, xx2] for xx1, xx2 in zip(x1, x2)]
    m = np.array(ar, float)
    x1_mean = statistics.mean(x1)
    x2_mean = statistics.mean(x2)
    for i in range(n):
        m[i,0] += rotateX(m[i,0], m[i,1], x1_mean, x2_mean, 45)
        m[i,1] += rotateY(m[i,0], m[i,1], x1_mean, x2_mean, 45)
    result = [get_class2(x, y) for x, y in zip(m[:,0], m[:,1])]
    plt.ylim(-20, 120)
    plt.xlim(-20, 120)
    for i in range(n):
        plt.plot(m[i,0], m[i,1], 'bo' if result[i] == 1 else 'ro')

    X_train = m
    y_train = result

    total_features = X_train.shape[1]
    print("========================\nTeste 3:\n")

    print(f"Dataset contém {X_train.shape[0]} registros e {total_features} features")

    X_train, X_test, y_train, y_test = train_test_split(X_train, y_train, test_size=0.3, random_state=0)

    print(f"Conjunto de trainamento contém {X_train.shape[0]} registros")
    print(f"Conjunto de testes contém {X_test.shape[0]} registros")

    acumulated_variance = 0.95
    n_components = get_components_to_achieve_variance(X_train, acumulated_variance)

    print(f"São necessários {n_components} componentes para atingir {acumulated_variance * 100}% de toda variância do conjunto de treinamento do dataset.")

    precisao = performance_with_n_components(X_train, X_test, y_train, y_test, 1)
    performance_with_n_components(X_train, X_test, y_train, y_test, 2)

    plt.title(f"Sem normalização z-score, precisão de {precisao}% usando 1 componente principal")

    plt.show()

def teste4():
    n = 150
    x1 = np.random.uniform(low=-15, high=60, size=(n,))
    x2 = np.random.uniform(low=-10, high=10, size=(n,))
    ar = [[xx1, xx2] for xx1, xx2 in zip(x1, x2)]
    m = np.array(ar, float)
    x1_mean = statistics.mean(x1)
    x2_mean = statistics.mean(x2)
    for i in range(n):
        m[i,0] += rotateX(m[i,0], m[i,1], x1_mean, x2_mean, 45)
        m[i,1] += rotateY(m[i,0], m[i,1], x1_mean, x2_mean, 45)
    result = [get_class2(x, y) for x, y in zip(m[:,0], m[:,1])]

    x1 = [x for x in m[:,0]]
    x2 = [x for x in m[:,1]]
    x1 = list(zscore_normalization(x1))
    x2 = list(zscore_normalization(x2))
    ar = [[xx1, xx2] for xx1, xx2 in zip(x1, x2)]
    m = np.matrix(ar, float)

    for i in range(n):
        plt.plot(m[i,0], m[i,1], 'bo' if result[i] == 1 else 'ro')

    X_train = m
    y_train = result

    total_features = X_train.shape[1]
    print("========================\nTeste 4:\n")

    print(f"Dataset contém {X_train.shape[0]} registros e {total_features} features")

    X_train, X_test, y_train, y_test = train_test_split(X_train, y_train, test_size=0.3, random_state=0)

    print(f"Conjunto de trainamento contém {X_train.shape[0]} registros")
    print(f"Conjunto de testes contém {X_test.shape[0]} registros")

    acumulated_variance = 0.95
    n_components = get_components_to_achieve_variance(X_train, acumulated_variance)

    print(f"São necessários {n_components} componentes para atingir {acumulated_variance * 100}% de toda variância do conjunto de treinamento do dataset.")

    precisao = performance_with_n_components(X_train, X_test, y_train, y_test, 1)
    performance_with_n_components(X_train, X_test, y_train, y_test, 2)

    plt.title(f"Com normalização z-score, precisão de {precisao}% usando 1 componente principal")

    plt.show()


if __name__ == "__main__":
    teste1()
    teste2()
    teste3()
    teste4()
