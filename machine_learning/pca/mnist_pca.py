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


def get_components_to_achieve_variance(X_train, desired_variance):
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)

    pca = PCA()
    X_train = pca.fit_transform(X_train)

    explained_variance = pca.explained_variance_ratio_

    n_components = 0
    acumulated_variance = 0

    for idx, variance in enumerate(explained_variance):
        acumulated_variance += variance
        n_components += 1
        if acumulated_variance >= desired_variance:
            break
    return n_components


if __name__ == "__main__":
    dataset = pd.read_csv("/home/bruno/git/Programming-Studies/machine_learning/pca/mnist_train.csv")

    X_train = dataset.drop(['label'], axis='columns', inplace=False)
    y_train = dataset['label']

    print(dataset.head())

    total_features = X_train.shape[1]

    print(f"Dataset contém {X_train.shape[0]} registros e {total_features} features")

    X_train, X_test, y_train, y_test = train_test_split(X_train, y_train, test_size=0.3, random_state=0)

    print(f"Conjunto de trainamento contém {X_train.shape[0]} registros")
    print(f"Conjunto de testes contém {X_test.shape[0]} registros")

    acumulated_variance = 0.95
    n_components = get_components_to_achieve_variance(X_train, acumulated_variance)

    print(f"São necessários {n_components} componentes para atingir {acumulated_variance * 100}% de toda variância do conjunto de treinamento do dataset.")

    performance_with_n_components(X_train, X_test, y_train, y_test, n_components)
    performance_with_n_components(X_train, X_test, y_train, y_test, 784)
