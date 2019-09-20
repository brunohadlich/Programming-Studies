#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "soma_array.h"

int main() {
	const int QT = 1000 * 1000 * 10;
	int *vetor = malloc(QT * sizeof(int));
	int i;
	for (i = 0; i < QT; i++) {
		vetor[i] = rand();
	}

	time_t t0 = clock();
	printf("Resultado da soma: %lld\n", soma_array(vetor, QT));
	time_t t1 = clock();
	printf("Tempo: %ld clocks\n", t1 - t0);
	return 0;
}
