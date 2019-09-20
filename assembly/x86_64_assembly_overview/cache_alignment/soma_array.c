#include "soma_array.h"

long long soma_array(struct data *vetor, int size) {
	long long soma = 0;
	int i;
	for (i = 0; i < size; i++) {
		soma += vetor[i].number3;
	}
	return soma;

}
