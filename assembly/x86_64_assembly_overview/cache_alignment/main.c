#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "soma_array.h"

int main() {
	printf("%lu\n", sizeof(struct data));
	const int QT = 1000 * 1000 * 10;
	struct data *vetor = malloc(QT * sizeof(struct data));
	printf("%lu\n", QT * sizeof(struct data));
	int i;
	for (i = 0; i < QT; i++) {
		vetor[i].number3 = rand();
	}

	time_t t0 = clock();
	printf("Resultado da soma: %lld\n", soma_array(vetor, QT));
	time_t t1 = clock();
	printf("Tempo: %ld clocks\n", t1 - t0);
	return 0;
}
