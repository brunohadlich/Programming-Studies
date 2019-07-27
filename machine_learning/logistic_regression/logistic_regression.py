import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score
from math import sqrt, exp, log
from time import sleep, time


def sigmoid(x):
    return 1 / (1 + exp(-x))


def hypothesis(theta, x):
    """
    >>> hypothesis([3, 4, 5], [1, 3, 4])
    35
    >>> hypothesis([7, 2, 9, 1], [1, 7, 1, 8])
    38
    >>> hypothesis([13, 7, 3, 2], [1, 10, 32, 7])
    193
    """
    return sigmoid(sum([theta[i] * x[i] for i in range(len(theta))]))


def cost_function(theta, X, Y):
    result = 0
    for x, y in zip(X, Y):
        h = hypothesis(theta, x)
        result += y * log(h) + (1 - y) * log(1 - h)

    return -(1 / len(X)) * result


def gradient_descent(x, y, max_iterations, alpha, convergence_threshold):
    iterations = 0
    convergence = 999999
    m = len(x)
    n = len(x[0])
    theta = [0] * n
    last_cost = cost_function(theta, x, y)
    history_cost_iteration = []
    while convergence > convergence_threshold and iterations < max_iterations:
        for j in range(n):
            result = 0
            for i in range(m):
                result += (hypothesis(theta, x[i]) - y[i]) * x[i][j]
            theta[j] -= (alpha / m) * result
        cost = cost_function(theta, x, y)
        convergence = abs(last_cost - cost)
        last_cost = cost
        iterations += 1
        history_cost_iteration.append(cost)
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
        result = 0
        for k in range(m):
            result += pow(x[k][i] - x_feature_mean[i], 2)
        x_feature_standard_deviation[i] = sqrt(1 / (m - 1) * result)
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


def predict(x_test, x_feature_mean, x_feature_sdv, theta):
    for i, x in enumerate(x_test):
        result = []
        for k in range(len(x)):
            result.append((x[k] - x_feature_mean[k]) / x_feature_sdv[k])
        x_test[i] = result
    x_test = [[1] + x_test[i] for i in range(len(x_test))]
    m = len(x_test)
    predictions = [0] * m
    i = 0
    for el in x_test:
        predictions[i] = 1 if hypothesis(theta, el) >= 0.5 else 0
        i = i + 1
    return predictions


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


def format_dataset(train):
    train["Age"] = train[["Age", "Pclass"]].apply(inpute_age, axis=1)
    train.drop("Cabin", axis=1, inplace=True)
    train.dropna(inplace=True)
    sex = pd.get_dummies(train["Sex"], drop_first=True)
    embark = pd.get_dummies(train["Embarked"], drop_first=True)
    train.drop(["Sex", "Embarked", "Name", "Ticket"], axis=1, inplace=True)
    train = pd.concat([train, sex, embark], axis=1)
    return train


def print_accuracy(y_test, predictions):
    print(classification_report(y_test, predictions))
    print("Accuracy:", accuracy_score(y_test, predictions))


def scikit_learn_solution():
    train = pd.read_csv("titanic_problem/train.csv")
    train = format_dataset(train)
    X_train, X_test, y_train, y_test = train_test_split(
        train.drop("Survived", axis=1),
        train["Survived"],
        test_size=0.30,
        random_state=101,
    )
    logmodel = LogisticRegression()
    logmodel.fit(X_train, y_train)
    predictions = logmodel.predict(X_test)
    print_accuracy(y_test, predictions)


def manual_solution():
    train = pd.read_csv("titanic_problem/train.csv")
    train = format_dataset(train)
    x_train, x_test, y_train, y_test = train_test_split(
        train.drop("Survived", axis=1),
        train["Survived"],
        test_size=0.30,
        random_state=101,
    )
    x_train = x_train.values.tolist()
    y_train = y_train.values.tolist()
    x_test = x_test.values.tolist()
    y_test = y_test.values.tolist()
    x_train, x_feature_mean, x_feature_sdv = feature_normalize(x_train)
    m = len(x_train)
    x_train = [[1] + x_train[i] for i in range(m)]
    iterations = 10000
    alpha = 0.01
    convergence_threshold = 0.000001
    theta, history_cost_iteration = gradient_descent(
        x_train, y_train, iterations, alpha, convergence_threshold
    )
    print("\nNumber of samples: {}.\n".format(m))
    print(
        (
            "Theta is equal to {} after {} gradient descent iterations using "
            "alpha equals to {} and convergence threshold of {} reaching a "
            "cost of {}.\n"
        ).format(
            theta,
            len(history_cost_iteration),
            alpha,
            convergence_threshold,
            cost_function(theta, x_train, y_train),
        )
    )
    predictions = predict(x_test, x_feature_mean, x_feature_sdv, theta)
    print_accuracy(y_test, predictions)


if __name__ == "__main__":
    start = time()
    manual_solution()
    end = time()
    print(f"manual_solution took {end - start}s to finish.")
    start = time()
    scikit_learn_solution()
    end = time()
    print(f"manual_solution took {end - start}s to finish.")
