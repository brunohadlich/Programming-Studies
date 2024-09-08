import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import minmax_scale
from scipy import stats
from math import pow, sqrt

N = 1000
np.random.seed(0)
#X = np.random.randint(-1000, 1000, N)
#X = np.random.randint(0, 1000, N)
X = np.random.randint(1000, 1500, N)

def mean(X):
    return sum(X) / len(X)

def mad(X):
    m = mean(X)
    return sum([x - m for x in X]) / (len(X) - 1)

def variance(X):
    m = mean(X)
    return sum([pow(x - m, 2) for x in X]) / (len(X) - 1)

def standard_deviation(X):
    return sqrt(variance(X))

#Normalize to a range of 0-1
def min_max_normalization(X):
    min_X = min(X)
    max_minus_min = max(X) - min_X
    for x in X:
        yield (x - min_X) / max_minus_min

#Normalize to the parameters minimum and maximum
def min_max_normalization2(X, minimum, maximum):
    min_X = min(X)
    max_minus_min = max(X) - min_X
    maximum_minus_minimum = maximum - minimum
    for x in X:
        yield minimum + ((x - min_X) * maximum_minus_minimum / max_minus_min)

#Normalize to a range of -0.5 to 0.5
def mean_normalization(X):
    max_minus_min = max(X) - min(X)
    mean_X = mean(X)
    for x in X:
        yield (x - mean_X) / max_minus_min

def zscore_normalization(X):
    m = len(X)
    X_mean = mean(X)
    X_sdv = standard_deviation(X)
    for x in X:
        yield (x - X_mean) / X_sdv

def print_data_info(title, X):
    print("----------------")
    print(title)
    qt_elements = len(X)
    sdv = standard_deviation(X)
    m = mean(X)
    print(f"Qty: {len(X)}")
    print(f"Min: {min(X)}")
    print(f"Max: {max(X)}")
    print(f"Mean: {m}")
    print(f"MAD: {mad(X)}")
    print(f"Variance: {variance(X)}")
    print(f"SDV: {sdv}")

    one_sdv_distance = 0
    two_sdv_distance = 0
    three_sdv_distance = 0
    for x in X:
        if (x >= m - sdv) and (x <= m + sdv):
            one_sdv_distance += 1
        if (x >= m - 2*sdv) and (x <= m + 2*sdv):
            two_sdv_distance += 1
        if (x >= m - 3*sdv) and (x <= m + 3*sdv):
            three_sdv_distance += 1
    print(f"One sdv distance: {one_sdv_distance} = {one_sdv_distance/qt_elements * 100}")
    print(f"Two sdv distance: {two_sdv_distance} = {two_sdv_distance/qt_elements * 100}")
    print(f"Three sdv distance: {three_sdv_distance} = {three_sdv_distance/qt_elements * 100}")
    print("----------------")

original_data = X

def plot(X, title):
    print_data_info(title, X)
    fig, ax=plt.subplots(1,2)
    sns.distplot(X, ax=ax[0])
    ax[0].set_title(title)
    plt.show()

def plot2(X, Y, X_title, Y_title):
    print_data_info(Y_title, Y)

    # plot both together to compare
    fig, ax=plt.subplots(1,2)
    sns.distplot(X, ax=ax[0])
    ax[0].set_title(X_title)
    sns.distplot(Y, ax=ax[1])
    ax[1].set_title(Y_title)
    plt.show()

total = 1000

distribution = np.random.standard_normal(size = total)
plot(distribution, "np.random.standard_normal(size = total)")

distribution = np.random.normal(size = total)
plot(distribution, "np.random.normal(size = total)")

distribution = np.random.normal(loc = 0, scale = 1, size = total)
plot(distribution, "np.random.normal(loc = 0, scale = 1, size = total)")

distribution = np.random.normal(loc = 0, scale = 5, size = total)
plot(distribution, "np.random.normal(loc = 0, scale = 5, size = total)")

distribution = np.random.normal(loc = 200, scale = 1, size = total)
plot(distribution, "np.random.normal(loc = 200, scale = 1, size = total)")

distribution = np.random.normal(loc = 200, scale = 5, size = total)
plot(distribution, "np.random.normal(loc = 200, scale = 5, size = total)")

distribution = list(zscore_normalization(np.random.normal(loc = 200, scale = 5, size = total)))
plot(distribution, "list(zscore_normalization(np.random.normal(loc = 200, scale = 5, size = total)))")

distribution = np.random.randint(-1000, 1000, total)
plot(distribution, "np.random.randint(-1000, 1000, total)")

distribution = np.random.randint(-1000, 1000, total)
distribution = list(zscore_normalization(distribution))
plot(distribution, "list(zscore_normalization(np.random.randint(-1000, 1000, total))")

plot([1, 2, 3, 4, 5], "[1, 2, 3, 4, 5]")
plot([1, 1, 3, 3, 7], "[1, 1, 3, 3, 7]")
plot([1, 1, 2, 3, 8], "[1, 1, 2, 3, 8]")
plot(list(mean_normalization([1, 2, 3, 4, 5])), "list(mean_normalization([1, 2, 3, 4, 5]))")
plot(list(mean_normalization([1, 1, 3, 3, 7])), "list(mean_normalization([1, 1, 3, 3, 7]))")
plot(list(mean_normalization([1, 1, 2, 3, 8])), "list(mean_normalization([1, 1, 2, 3, 8]))")
exit(0)



print("-------")
print_data_info("Original data", original_data)
print("-------")
plot2(original_data, list(min_max_normalization(original_data)), "Original data", "min-max normalization")
print("-------")
plot2(original_data, list(min_max_normalization2(original_data, 10, 20)), "Original data", "min-max normalization2")
print("-------")
plot2(original_data, list(mean_normalization(original_data)), "Original data", "mean normalization")
print("-------")
plot2(original_data, list(zscore_normalization(original_data)), "Original data", "zscore normalization")
