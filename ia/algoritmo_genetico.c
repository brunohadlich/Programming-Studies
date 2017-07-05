#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int QUANTIDADE_CIDADES;
int QUANTIDADE_GENES;
int QUANTIDADE_TESTES;

int id_cromossomo = 1;

struct gene_cidade {
	int cidade;
	double x;
	double y;
} gene_cidade;

struct gene_cidade *create_gene_cidade(int cidade, double x, double y) {
	struct gene_cidade* gene_cidade = malloc(sizeof(struct gene_cidade));
	gene_cidade -> cidade = cidade;
	gene_cidade -> x = x;
	gene_cidade -> y = y;
	return gene_cidade;
}

void free_gene_cidade(struct gene_cidade* gene_cidade) {
	free(gene_cidade);
}

struct genes_cidade {
	int quantidade;
	struct gene_cidade** genes;
} genes_cidade;

struct genes_cidade *create_genes_cidade(int quantidade, struct gene_cidade** genes) {
	struct genes_cidade *genes_cidade = malloc(sizeof(struct genes_cidade));
	genes_cidade -> quantidade = quantidade;
	genes_cidade -> genes = genes;
	return genes_cidade;
}

struct genes_cidade *create_genes_cidade_from(int quantidade, struct gene_cidade** genes, int index_init) {
	struct gene_cidade** new_genes = (struct gene_cidade**)malloc(quantidade * sizeof(struct gene_cidade*));
	int i, k;
	new_genes[0] = genes[0];
	for (i = 1; i < index_init; i++)
		new_genes[quantidade - i - 1] = genes[i];
	for (i = index_init, k = 1; i < quantidade - 1; i++)
		new_genes[k++] = genes[i];
	new_genes[quantidade - 1] = genes[quantidade - 1];
	struct genes_cidade * genes_cidade = create_genes_cidade(quantidade, new_genes);
	return genes_cidade;
}

void free_genes_cidade(struct genes_cidade *genes_cidade) {
	int i;
	for (i = 0; i < genes_cidade -> quantidade; i++)
		free_gene_cidade(genes_cidade -> genes[i]);
	free(genes_cidade -> genes);
	free(genes_cidade);
}

struct cromossomo {
	int id;
	struct genes_cidade *genes_cidade;
	double fitness_status;
} cromossomo;

struct cromossomo *create_cromossomo(int id, struct genes_cidade *genes_cidade, double fitness_status) {
	struct cromossomo * cromossomo = (struct cromossomo *)malloc(sizeof(struct cromossomo));
	cromossomo -> id = id;
	cromossomo -> genes_cidade = genes_cidade;
	cromossomo -> fitness_status = fitness_status;
	return cromossomo;
}

void free_cromossomo(struct cromossomo * cromossomo) {
	free_genes_cidade(cromossomo -> genes_cidade);
	free(cromossomo);
}

struct populacao {
	int quantidade;
	struct cromossomo** cromossomos;
} populacao;

double random_zero_one() {
	return (double)rand()/(double)RAND_MAX;
}

struct gene_cidade **create_genes_populacao() {
	struct gene_cidade** genes = (struct gene_cidade**)malloc(QUANTIDADE_GENES * sizeof(struct gene_cidade*));
	int i;
	for (i = 0; i < QUANTIDADE_GENES - 1; i++)
		genes[i] = create_gene_cidade(i, random_zero_one(),random_zero_one());
	genes[i] = create_gene_cidade(i, genes[0] -> x, genes[0] -> y);
	return genes;
}

void print_genes(struct genes_cidade* genes) {
	int i;
	for (i = 0; i < genes -> quantidade; i++)
		printf("%d: x:%f, y:%f\n", genes -> genes[i] -> cidade, genes -> genes[i] -> x, genes -> genes[i] -> y);
}

struct populacao* create_populacao() {
	struct populacao* populacao = malloc(sizeof(struct populacao));
	populacao -> quantidade = QUANTIDADE_CIDADES;
	struct gene_cidade **genes = create_genes_populacao();
	populacao -> cromossomos = (struct cromossomo**)malloc(populacao -> quantidade * sizeof(struct cromossomo*));
	int i;
	for (i = 0; i < populacao -> quantidade; i++) {
		struct genes_cidade *genes_cidade = create_genes_cidade_from(QUANTIDADE_GENES, genes, i+1);
		populacao -> cromossomos[i] = create_cromossomo(id_cromossomo++, genes_cidade, 0);
	}
	return populacao;
}

void free_populacao(struct populacao* populacao) {
	int i;
	for (i = 0; i < populacao -> quantidade; i++)
		free_cromossomo(populacao -> cromossomos[i]);
	free(populacao -> cromossomos);
	free(populacao);
}

double funcao_aptidao_distancia(const struct cromossomo* cromossomo) {
	int i;
	double fitness = 0;
	for (i = 0; i < cromossomo -> genes_cidade -> quantidade - 1; i++)
		fitness += sqrt(pow(cromossomo -> genes_cidade -> genes[i + 1] -> x - cromossomo -> genes_cidade -> genes[i] -> x, 2) +
						pow(cromossomo -> genes_cidade -> genes[i + 1] -> y - cromossomo -> genes_cidade -> genes[i] -> y, 2));
	return fitness;
}

int compare_cromossomo(const void *c1, const void *c2) {
	const struct cromossomo **cr1 = (const struct cromossomo **)c1;
	const struct cromossomo **cr2 = (const struct cromossomo **)c2;
	double func_cr1 = funcao_aptidao_distancia((const struct cromossomo *)*cr1);
	double func_cr2 = funcao_aptidao_distancia((const struct cromossomo *)*cr2);
	if (func_cr1 > func_cr2)
		return 1;
	else if (func_cr1 < func_cr2)
		return -1;
	else
		return 0;
}

struct item_roleta {
	double pontuacao_de;
	double pontuacao_ate;
	int pego;
	struct cromossomo * cromossomo;
} item_roleta;

struct item_roleta *create_item_roleta(double pontuacao_de, double pontuacao_ate, struct cromossomo* cromossomo) {
	struct item_roleta *item_roleta = (struct item_roleta *)malloc(sizeof(struct item_roleta));
	item_roleta -> pontuacao_de = pontuacao_de;
	item_roleta -> pontuacao_ate = pontuacao_ate;
	item_roleta -> cromossomo = cromossomo;
	item_roleta -> pego = 0;
	return item_roleta;
}

void free_item_roleta(struct item_roleta *item_roleta) {
	if (item_roleta -> pego == 0)
		free_cromossomo(item_roleta -> cromossomo);
	free(item_roleta);
}

struct itens_roleta {
	int quantidade;
	struct item_roleta **itens;
} itens_roleta;

struct itens_roleta* create_itens_roleta(int quantidade) {
	struct itens_roleta *itens_roleta = (struct itens_roleta *)malloc(sizeof(struct itens_roleta));
	itens_roleta -> quantidade = quantidade;
	itens_roleta -> itens = (struct item_roleta **)malloc(quantidade * sizeof(struct item_roleta *));
	int i;
	for (i = 0; i < itens_roleta -> quantidade; i++)
		itens_roleta -> itens[i] = NULL;
	return itens_roleta;
}

struct cromossomo *pega_cromossomo_roleta(struct itens_roleta *roleta, double soma_itens_roleta) {
	struct cromossomo *cromossomo = NULL;
	while (cromossomo == NULL) {
		double rand_val = fmod(rand(),soma_itens_roleta);
		int k;
		for (k = 0; k < roleta -> quantidade; k++) {
			if ((roleta -> itens[k] -> pego == 0) && 
				(roleta -> itens[k] -> pontuacao_de  <= rand_val) && 
				(roleta -> itens[k] -> pontuacao_ate >= rand_val)) {
				cromossomo = roleta -> itens[k] -> cromossomo;
				roleta -> itens[k] -> pego = 1;
				break;
			}
		}
	}
	return cromossomo;
}

void copia_genes(struct cromossomo *from, struct cromossomo *to) {
	int i;
	for (i = 0; i < from -> genes_cidade -> quantidade; i++)
		to -> genes_cidade -> genes[i] = create_gene_cidade(from -> genes_cidade -> genes[i] -> cidade, 
															from -> genes_cidade -> genes[i] -> x,
															from -> genes_cidade -> genes[i] -> y);
}

int duplicado(struct cromossomo* c) {
	int i, k;
	for (i = 1; i < c -> genes_cidade -> quantidade - 2; i++)
		for (k = i + 1; k < c -> genes_cidade -> quantidade; k++)
			if (c -> genes_cidade -> genes[i] -> cidade == c -> genes_cidade -> genes[k] -> cidade)
				return 1;
	return 0;
}

struct cromossomo **crossover(struct cromossomo *c1, struct cromossomo *c2) {
	struct gene_cidade **genes = (struct gene_cidade **)malloc(QUANTIDADE_GENES * sizeof(struct gene_cidade*));
	struct genes_cidade *genes_cidade = create_genes_cidade(QUANTIDADE_GENES, genes);
	struct cromossomo *cr1 = create_cromossomo(id_cromossomo++, genes_cidade, 0);
	copia_genes(c1, cr1);
	struct gene_cidade **genes2 = (struct gene_cidade **)malloc(QUANTIDADE_GENES * sizeof(struct gene_cidade*));
	struct genes_cidade *genes_cidade2 = create_genes_cidade(QUANTIDADE_GENES, genes2);
	struct cromossomo *cr2 = create_cromossomo(id_cromossomo++, genes_cidade2, 0);
	copia_genes(c2, cr2);
	int idx_cross = rand() % (int)QUANTIDADE_GENES;
	while ((idx_cross == 0) || (idx_cross == QUANTIDADE_GENES - 1))
		idx_cross = rand() % QUANTIDADE_GENES;
	struct gene_cidade *pivo = cr1 -> genes_cidade -> genes[idx_cross];
	cr1 -> genes_cidade -> genes[idx_cross] = cr2 -> genes_cidade -> genes[idx_cross];
	cr2 -> genes_cidade -> genes[idx_cross] = pivo;
	while (duplicado(cr1) || duplicado(cr2)) {
		idx_cross = rand() % QUANTIDADE_GENES;
		pivo = cr1 -> genes_cidade -> genes[idx_cross];
		cr1 -> genes_cidade -> genes[idx_cross] = cr2 -> genes_cidade -> genes[idx_cross];
		cr2 -> genes_cidade -> genes[idx_cross] = pivo;
	}
	struct cromossomo **cromossomos = (struct cromossomo **)malloc(2*sizeof(struct cromossomo *));
	cromossomos[0] = cr1;
	cromossomos[1] = cr2;
	return cromossomos;
}

void limpa_itens_roleta(struct itens_roleta *roleta) {
	int i;
	for (i = 0; i < roleta -> quantidade; i++)
		free_item_roleta(roleta -> itens[i]);
}

void mutar(struct populacao* populacao) {
	int gene_aleatorio1 = rand()%QUANTIDADE_GENES;
	while ((gene_aleatorio1 == 0) || (gene_aleatorio1 == QUANTIDADE_GENES - 1))
		gene_aleatorio1 = rand() % QUANTIDADE_GENES;
	int gene_aleatorio2 = rand()%QUANTIDADE_GENES;
	while ((gene_aleatorio2 == 0) || (gene_aleatorio2 == QUANTIDADE_GENES - 1))
		gene_aleatorio2 = rand() % QUANTIDADE_GENES;
	while (gene_aleatorio2 == gene_aleatorio1) {
		gene_aleatorio2 = rand() % QUANTIDADE_GENES;
		while ((gene_aleatorio2 == 0) || (gene_aleatorio2 == QUANTIDADE_GENES - 1))
			gene_aleatorio2 = rand() % QUANTIDADE_GENES;
	}
	
	int cromossomo_aleatorio = rand()%QUANTIDADE_CIDADES;
	
	struct gene_cidade * pivo = populacao -> cromossomos[cromossomo_aleatorio] -> genes_cidade -> genes[gene_aleatorio1];
	populacao -> cromossomos[cromossomo_aleatorio] -> genes_cidade -> genes[gene_aleatorio1] = populacao -> cromossomos[cromossomo_aleatorio] -> genes_cidade -> genes[gene_aleatorio2];
	populacao -> cromossomos[cromossomo_aleatorio] -> genes_cidade -> genes[gene_aleatorio2] = pivo;
}

struct melhor_resultado {
	double melhor_fitness;
	struct cromossomo *cromossomo;
} melhor_resultado;

void free_melhor_resultado(struct melhor_resultado *melhor_resultado) {
	free_cromossomo(melhor_resultado -> cromossomo);
	free(melhor_resultado);
}

struct gene_cidade *copiar_gene_cidade(struct gene_cidade *gene_cidade) {
	struct gene_cidade *copia_gene_cidade = (struct gene_cidade *)malloc(sizeof(struct gene_cidade));
	copia_gene_cidade -> cidade = gene_cidade -> cidade;
	copia_gene_cidade -> x = gene_cidade -> x;
	copia_gene_cidade -> y = gene_cidade -> y;
	return copia_gene_cidade;
}

struct cromossomo *copia_cromossomo(struct cromossomo *cromossomo) {
	struct cromossomo *copia_cromossomo = (struct cromossomo *)malloc(sizeof(struct cromossomo));
	copia_cromossomo -> id = cromossomo -> id;
	struct gene_cidade **copia_gene_cidade = (struct gene_cidade **)malloc(cromossomo -> genes_cidade -> quantidade * sizeof(struct gene_cidade *));
	int i;
	for (i = 0; i < cromossomo -> genes_cidade -> quantidade; i++)
		copia_gene_cidade[i] = copiar_gene_cidade(cromossomo -> genes_cidade -> genes[i]);
	copia_cromossomo -> genes_cidade = create_genes_cidade(cromossomo -> genes_cidade -> quantidade, copia_gene_cidade);
	copia_cromossomo -> fitness_status = cromossomo -> fitness_status;
	return copia_cromossomo;
}

struct populacao *copia_populacao(struct populacao *populacao) {
	struct populacao* populacao_copia = malloc(sizeof(struct populacao));
	populacao_copia -> quantidade  = populacao -> quantidade;
	populacao_copia -> cromossomos = (struct cromossomo**)malloc(populacao_copia -> quantidade * sizeof(struct cromossomo*));
	int i;
	for (i = 0; i < populacao_copia -> quantidade; i++)
		populacao_copia -> cromossomos[i] = copia_cromossomo(populacao -> cromossomos[i]);
	return populacao_copia;
}

struct melhor_resultado *processa_populacao(struct populacao *populacao) {
	srand(time(NULL));
	struct cromossomo *melhor_cromossomo = NULL;
	double melhor_fitness = 999999;
	struct itens_roleta *roleta = create_itens_roleta(QUANTIDADE_CIDADES);
	int iteracoes;
	for (iteracoes = 0; iteracoes < 10000; iteracoes++) {
		qsort(populacao -> cromossomos, QUANTIDADE_CIDADES, sizeof(struct cromossomo*), compare_cromossomo);
		double soma_itens_roleta_ant = 0;
		double soma_itens_roleta = 0;
		int i;
		for (i = 0; i < populacao -> quantidade; i++) {
			populacao -> cromossomos[i] -> fitness_status = funcao_aptidao_distancia(populacao -> cromossomos[i]);
			if (populacao -> cromossomos[i] -> fitness_status < melhor_fitness) {
				melhor_fitness = populacao -> cromossomos[i] -> fitness_status;
				if (melhor_cromossomo != NULL)
					free_cromossomo(melhor_cromossomo);
				melhor_cromossomo = copia_cromossomo(populacao -> cromossomos[i]);
			}
			
			soma_itens_roleta += (double)((double)1.0 / populacao -> cromossomos[i] -> fitness_status);
			roleta -> itens[i] = create_item_roleta(soma_itens_roleta_ant, soma_itens_roleta, populacao -> cromossomos[i]);
			soma_itens_roleta_ant = soma_itens_roleta;
		}
		int metade;
		if ((populacao -> quantidade & 1) > 0)
			metade = (int)(populacao -> quantidade / 2) + 1;
		else
			metade = (int)(populacao -> quantidade / 2);
		for (i = 0; i < metade; i++)
			populacao -> cromossomos[i]	= pega_cromossomo_roleta(roleta, soma_itens_roleta);
		limpa_itens_roleta(roleta);
		while (i < populacao -> quantidade) {
			struct cromossomo ** cromossomos = crossover(populacao -> cromossomos[0], populacao -> cromossomos[1]);
			populacao -> cromossomos[i++] = cromossomos[0];
			if (i < populacao -> quantidade)
				populacao -> cromossomos[i++] = cromossomos[1];
			else
				free_cromossomo(cromossomos[1]);
			free(cromossomos);
		}
		mutar(populacao);
		
		soma_itens_roleta = 0;
	}
	free(roleta);

	struct melhor_resultado *melhor_resultado = (struct melhor_resultado *)malloc(sizeof(struct melhor_resultado));
	melhor_resultado -> melhor_fitness = melhor_fitness;
	melhor_resultado -> cromossomo = melhor_cromossomo;

	printf("Melhor custo: %f\nMelhor solução:", melhor_fitness);
	int i;
	for (i = 0; i < melhor_cromossomo -> genes_cidade -> quantidade; i++)
		printf(" %d", melhor_cromossomo -> genes_cidade -> genes[i] -> cidade);
	printf("\n");
	
	return melhor_resultado;
}

struct populacao *read_populacao(char *file_name) {
	FILE *f = fopen(file_name, "r");
	if (f == NULL) {
		printf("Arquivo invalido!");
		exit(EXIT_FAILURE);
	} else {
		int ret = fscanf(f, "%d", &QUANTIDADE_TESTES);
		ret = fscanf(f, "%d", &QUANTIDADE_CIDADES);
		QUANTIDADE_GENES = QUANTIDADE_CIDADES + 1;
		printf("%d\n", QUANTIDADE_CIDADES);
		if (ret != 1)
			printf("Houve um erro na leitura da quantidade de cidades do arquivo!");
		struct populacao *populacao = (struct populacao *)malloc(QUANTIDADE_CIDADES * sizeof(struct populacao *));
		populacao -> quantidade = QUANTIDADE_CIDADES;
		struct gene_cidade **genes = (struct gene_cidade **)malloc((QUANTIDADE_CIDADES + 1) * sizeof(struct gene_cidade*));
		int i;
		for (i = 0; i < QUANTIDADE_CIDADES; i++) {
			genes[i] = create_gene_cidade(0, 0, 0);
			ret = fscanf(f, "%d %lf %lf", &genes[i] -> cidade, &genes[i] -> x, &genes[i] -> y);
			if (ret != 3)
				printf("Houve um erro na leitura dos dados das cidades do arquivo!");
		}
		genes[i] = create_gene_cidade(genes[0] -> cidade, genes[0] -> x, genes[0] -> y);
		fclose(f);
		return populacao;
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Favor informar o nome do arquivo de população no formato path/filename!");
		exit(EXIT_FAILURE);
	} else {
		struct populacao *populacao = read_populacao(argv[1]);
		populacao = create_populacao();
		print_genes(populacao -> cromossomos[0] -> genes_cidade);
		double melhor_fitness = 999999;
		struct cromossomo *melhor_cromossomo = NULL;
		int i;
		for (i = 0; i < QUANTIDADE_TESTES; i++) {
			struct populacao *copia = copia_populacao(populacao);
			struct melhor_resultado *melhor_resultado = processa_populacao(copia);
			free_populacao(copia);
			if (melhor_fitness > melhor_resultado -> melhor_fitness) {
				melhor_fitness = melhor_resultado -> melhor_fitness;
				melhor_cromossomo = copia_cromossomo(melhor_resultado -> cromossomo);
			}
			free_melhor_resultado(melhor_resultado);
		}
		free_populacao(populacao);
		printf("Melhor custo após %d resultados: %f\nMelhor solução:", QUANTIDADE_TESTES, melhor_fitness);		
		for (i = 0; i < melhor_cromossomo -> genes_cidade -> quantidade; i++)
			printf(" %d", melhor_cromossomo -> genes_cidade -> genes[i] -> cidade);
		printf("\n");
		return 0;
	}
}
