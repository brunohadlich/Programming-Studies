class Cidade:
    def __init__(self, id, distancia_linha_reta):
        self.id = id
        self.distancia_linha_reta = distancia_linha_reta
        self.cidades_vizinhas = {}
        self.pai = None
        self.distancia_da_origem = 999999

    def distancia_para(self, cidade):
        return self.cidades_vizinhas[cidade.id][1]

    def adicionar_cidade_vizinha(self, cidade, distancia):
        if not cidade.id in self.cidades_vizinhas:
            self.cidades_vizinhas[cidade.id] = (cidade, distancia)
            cidade.cidades_vizinhas[self.id] = (self, distancia)

    def distancia_ate_aqui(self):
        if self.pai == None:
            return 0
        else:
            return self.pai.distancia_da_origem + self.pai.distancia_para(self)

    def A(self, cidade_destino):
        self.distancia_da_origem = 0
        caminhos = [self]
        while len(caminhos) > 0:
            cidade_menor_distancia = None

            for cidade in caminhos:
                if cidade_menor_distancia == None or cidade.distancia_ate_aqui() + cidade.distancia_linha_reta < cidade_menor_distancia.distancia_ate_aqui() + cidade_menor_distancia.distancia_linha_reta:
                    cidade_menor_distancia = cidade

            print("Escolheu {}".format(cidade_menor_distancia.id))

            if cidade_menor_distancia == cidade_destino:
                return cidade_destino

            caminhos.remove(cidade_menor_distancia)

            vizinhos = [c[0] for c in cidade_menor_distancia.cidades_vizinhas.values()]

            for cidade in vizinhos:
                if cidade != self and cidade.pai == None or cidade_menor_distancia.distancia_da_origem + cidade_menor_distancia.distancia_para(cidade) < cidade.distancia_ate_aqui():
                    cidade.distancia_da_origem = cidade_menor_distancia.distancia_da_origem + cidade_menor_distancia.distancia_para(cidade)
                    cidade.pai = cidade_menor_distancia
                    if not cidade in caminhos:
                        print("Adicionou {}. Distância da origem: {}. Distância do pai {} até aqui: {}. g + h = {}".format(cidade.id, cidade.distancia_da_origem, cidade.pai.id, cidade.pai.distancia_para(cidade), cidade.distancia_da_origem + cidade.distancia_linha_reta))
                        caminhos.append(cidade)
                    else:
                        print("Alterou a distância da origem até {} para: {}. g + h = {}".format(cidade.id, cidade.distancia_da_origem, cidade.distancia_da_origem + cidade.distancia_linha_reta))

        return None


A = Cidade('A', 230)
B = Cidade('B', 182)
C = Cidade('C', 179)
D = Cidade('D', 165)
E = Cidade('E', 166)
F = Cidade('F', 160)
G = Cidade('G', 155)
H = Cidade('H', 137)
I = Cidade('I', 117)
J = Cidade('J', 115)
K = Cidade('K', 113)
L = Cidade('L', 100)
M = Cidade('M', 97)
N = Cidade('N', 73)
O = Cidade('O', 70)
P = Cidade('P', 61)
Q = Cidade('Q', 61)
R = Cidade('R', 0)

A.adicionar_cidade_vizinha(B, 73)
A.adicionar_cidade_vizinha(C, 64)
A.adicionar_cidade_vizinha(D, 89)
A.adicionar_cidade_vizinha(E, 104)
B.adicionar_cidade_vizinha(K, 83)
C.adicionar_cidade_vizinha(I, 64)
D.adicionar_cidade_vizinha(N, 89)
E.adicionar_cidade_vizinha(J, 40)
F.adicionar_cidade_vizinha(I, 31)
F.adicionar_cidade_vizinha(N, 84)
G.adicionar_cidade_vizinha(J, 35)
G.adicionar_cidade_vizinha(Q, 113)
H.adicionar_cidade_vizinha(K, 35)
H.adicionar_cidade_vizinha(L, 36)
I.adicionar_cidade_vizinha(L, 28)
I.adicionar_cidade_vizinha(M, 20)
J.adicionar_cidade_vizinha(N, 53)
J.adicionar_cidade_vizinha(Q, 80)
L.adicionar_cidade_vizinha(P, 63)
M.adicionar_cidade_vizinha(O, 50)
O.adicionar_cidade_vizinha(P, 41)
O.adicionar_cidade_vizinha(R, 72)
P.adicionar_cidade_vizinha(R, 65)
Q.adicionar_cidade_vizinha(R, 65)

v = A.A(R)
d = v.distancia_da_origem

s = []

while v != None:
    s.append(v)
    v = v.pai

print("Caminho entre A e R: ", end="")

while len(s) > 0:
    if len(s) > 1:
        seta = "-> "
    else:
        seta = "\n"
    print("{} {}".format(s.pop().id, seta), end="")

print("Distância entre A e R: {}".format(d))
