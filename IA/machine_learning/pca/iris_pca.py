import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
from warnings import simplefilter
simplefilter(action='ignore', category=FutureWarning)


def explain_variance_with_n_components(X, y, n_components, zscore = True):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)

    if zscore:
        sc = StandardScaler()
        X_train = sc.fit_transform(X_train)
        X_test = sc.transform(X_test)

    pca = PCA(n_components)
    X_train = pca.fit_transform(X_train)
    X_test = pca.transform(X_test)

    explained_variance = pca.explained_variance_ratio_

    print(f"Variância com {n_components} componentes:")
    for idx, variance in enumerate(explained_variance):
        print(f"Componente {idx} armazena {variance * 100}% da variância do dataset")
    print()


def performance_with_n_components(X, y, n_components, zscore = True):
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)

    if zscore:
        sc = StandardScaler()
        X_train = sc.fit_transform(X_train)
        X_test = sc.transform(X_test)

    pca = PCA(n_components)
    X_train = pca.fit_transform(X_train)
    X_test = pca.transform(X_test)

    classifier = RandomForestClassifier(max_depth=2, random_state=0)
    classifier.fit(X_train, y_train)

    y_pred = classifier.predict(X_test)

    cm = confusion_matrix(y_test, y_pred)
    print(f"Precisão treinando com {n_components} componente(s): {accuracy_score(y_test, y_pred)*100}%\n")

def training(X, y, zscore = True):
    explain_variance_with_n_components(X, y, 4, zscore)
    performance_with_n_components(X, y, 4, zscore)
    explain_variance_with_n_components(X, y, 3, zscore)
    performance_with_n_components(X, y, 3, zscore)
    explain_variance_with_n_components(X, y, 2, zscore)
    performance_with_n_components(X, y, 2, zscore)
    explain_variance_with_n_components(X, y, 1, zscore)
    performance_with_n_components(X, y, 1, zscore)


if __name__ == "__main__":
    names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'Class']
    dataset = pd.read_csv("/home/bruno/git/Programming-Studies/machine_learning/pca/iris.csv", names=names)

    print(dataset.head())

    X = dataset.drop('Class', 1)
    y = dataset['Class']

    print(f"\nDataset contém {X.shape[0]} registros e {X.shape[1]} features\n")

    print("Treinamentos com normalização z-score:\n")
    training(X, y)

    #print("Treinamentos sem normalização z-score:\n")
    #training(X, y, False)
