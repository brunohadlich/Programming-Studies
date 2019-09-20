long long soma_array(int *vetor, int size) {
	long long soma = 0;
	int i;
	for (i = 0; i < size; i++) {
		soma += vetor[i];
	}
	return soma;

}
