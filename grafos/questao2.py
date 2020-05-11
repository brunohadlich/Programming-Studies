import sys
from time import time

class Graph:
    edges = {}
    n_vertexes = 0

    def __init__(self, n_vertexes, use_matrix):
        self.n_vertexes = n_vertexes
        if use_matrix:
            self.vertexes = []
            for i in range(n_vertexes):
                self.vertexes.append([])
                for k in range(n_vertexes):
                    self.vertexes[i - 1].append(0)

    def add_undirected_edge(self, v1, v2):
        if v1 in self.edges:
            if not v2 in self.edges[v1]:
                self.edges[v1].append(v2)
        else:
            self.edges[v1] = [v2]
        if v2 in self.edges:
            if not v1 in self.edges[v2]:
                self.edges[v2].append(v1)
        else:
            self.edges[v2] = [v1]

    def qt_undirected_edges(self):
        qt_edges = 0
        for e in self.edges.values():
            qt_edges += len(e)
        return int(qt_edges / 2)

    def undirected_degree_sequence(self):
        degrees = {}
        for k in self.edges.keys():
            if not k in degrees:
                degrees[k] = 0
            for e in self.edges[k]:
                degrees[k] += 1
                if e in degrees:
                    degrees[e] += 1
                else:
                    degrees[e] = 1
        degree_sequence = list(degrees.values())
        degree_sequence += [0] * (self.n_vertexes - len(degree_sequence))
        degree_sequence.sort()
        degree_sequence.reverse()
        degrees = [int(x/2) for x in degree_sequence]
        return degrees

    def print_adjacent_matrix(self):
        matrix = []
        for i in range(self.n_vertexes):
            e = []
            for k in range(self.n_vertexes):
                e.append(-1)
            matrix.append(e)

        for k in self.edges.keys():
            for e in self.edges[k]:
                matrix[k-1][e-1] = 1

        for vertex_edges in matrix:
            for edge in vertex_edges:
                print("{} ".format(edge), end="")
            print("")

    def print_adjacent_vector(self):
        for i in range(1, self.n_vertexes + 1):
            if i in self.edges:
                print("{}: {}".format(i, ", ".join(map(str, self.edges[i]))))
            else:
                print("{}: ".format(i))

    def dfs(self, beginning_vertex):
        dfs_file = open("profundidade.txt", "w")
        traversed = [False] * self.n_vertexes

        def internal_dfs(traversed_array, first_vertex, parent, level):
            v = first_vertex
            traversed_array[v - 1] = True
            dfs_file.write("Vértice: {}; Pai: {}; Profundidade: {}.\n".format(first_vertex, parent, level))
            if v in self.edges:
                for e in self.edges[v]:
                    if not traversed_array[e - 1]:
                        internal_dfs(traversed_array, e, v, level + 1)

        internal_dfs(traversed, beginning_vertex, "-", 0)
        dfs_file.close()

    def iterative_dfs(self, beginning_vertex):
        dfs_file = open("profundidade.txt", "w")
        traversed = [False] * self.n_vertexes
        profundidade = [0] * self.n_vertexes
        pais = [-1] * self.n_vertexes
        pais[beginning_vertex - 1] = "-"
        q = [beginning_vertex]
        while len(q) > 0:
            v = q.pop()
            if not traversed[v - 1]:
                dfs_file.write("Vértice: {}; Pai: {}; Profundidade: {}.\n".format(v, pais[v - 1], profundidade[v - 1]))
                traversed[v - 1] = True
            if v in self.edges:
                for e in self.edges[v]:
                    if not traversed[e - 1]:
                        q.append(e)
                        pais[e - 1] = v
                        profundidade[e - 1] = profundidade[v - 1] + 1
        dfs_file.close()

    def bfs(self, beginning_vertex):
        bfs_file = open("largura.txt", "w")
        traversed = [False] * self.n_vertexes
        stack = [[beginning_vertex, 0]]
        traversed[beginning_vertex - 1] = True
        bfs_file.write("Vértice: {}; Pai: {}; Profundidade: {}.\n".format(beginning_vertex, "-", 0))

        while len(stack) > 0:
            v1, depth = stack.pop(0)
            if v1 in self.edges:
                for e in self.edges[v1]:
                    if not traversed[e - 1]:
                        traversed[e - 1] = True
                        bfs_file.write("Vértice: {}; Pai: {}; Profundidade: {}.\n".format(e, v1, depth + 1))
                        stack.append([e, depth + 1])

        bfs_file.close()

def questao1():
    if len(sys.argv) == 1:
        print("Favor informar o nome do arquivo a ser processado")
        return
    file_name = sys.argv[1]
    try:
        f = open(file_name, "r")
    except:
        print("Não foi possível ler o arquivo informado")
        return
    try:
        output_file = open("saida.txt", "w")
    except:
        print("Não foi possível criar o arquivo saida.txt")
        return
    g = Graph(int(f.readline()), False)
    n_vertexes_str = "Número de vértices: {}\n".format(g.n_vertexes)
    output_file.write(n_vertexes_str)
    for line in f.readlines():
        v1, v2 = line.split()
        v1 = int(v1)
        v2 = int(v2)
        g.add_undirected_edge(v1, v2)
    n_edges_str = "Número de arestas: {}\n".format(g.qt_undirected_edges())
    output_file.write(n_edges_str)
    degree_sequence_str = "Sequência de grau: {}\n".format(', '.join(map(str, g.undirected_degree_sequence())))
    output_file.write(degree_sequence_str)
    print("\nNúmero de vértices, número de arestas e sequência de grau armazenados no arquivo saida.txt\n")
    answer = input("Digite:\n\n1 - Para imprimir a matriz de adjacência.\n2 - Para o vetor de adjacência.\n3 - Para pular etapa.\n\nOpção: ")
    if answer == "1":
        g.print_adjacent_matrix()
    elif answer == "2":
        g.print_adjacent_vector()
    elif answer != "3":
        print("\nResposta inválida, saindo.\n")
        f.close()
        output_file.close()
        sys.exit(0)
    answer = int(input("\nInforme o vértice inicial para que sejam feitas as buscas em profundidade e em largura que serão salvas nos arquivos profundidade.txt e largura.txt. Vértice: "))
    if answer > g.n_vertexes:
        print("Vértice inválido, saindo.")
        f.close()
        output_file.close()
        return
    else:
        t0 = time()
        g.iterative_dfs(answer)
        t1 = time()
        print("Busca em profundidade levou {} segundos".format(t1 - t0))
        t0 = time()
        g.bfs(answer)
        t1 = time()
        print("Busca em largura levou {} segundos".format(t1 - t0))
    f.close()
    output_file.close()

questao1()
