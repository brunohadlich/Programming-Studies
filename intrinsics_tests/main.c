#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "my_intrinsics.h"

void fill_random_float(float *f, int size) {
	int i;

	for (i = 0; i < size; i++) {
		f[i] = rand();
	}
}

void add_floats_basic(float *f1, float *f2, float *f3, int size) {
	int i;

	for (i = 0; i < size; i++) {
		f3[i] = f1[i] + f2[i];
	}
}

int main(int argc, char **argv) {
	const int size = 8000095;

	float *f1 = (float *)malloc(size * sizeof(float));
	float *f2 = (float *)malloc(size * sizeof(float));
	float *f3 = (float *)malloc(size * sizeof(float));

	srand(time(NULL));

	fill_random_float(f1, size);
	fill_random_float(f2, size);
	fill_random_float(f3, size);

	clock_t t0 = clock();

	add_floats_basic(f1, f2, f3, size);

	clock_t t1 = clock();

	printf("Basic array sum(%d iterations):\n", size);
	printf("=============\n");
	printf("Time: %ld\n", t1 - t0);
	printf("f[3]=%f\n", f3[7]);
	printf("t0=%ld\n", t0);
	printf("t1=%ld\n", t1);
	printf("=============\n");

	t0 = clock();

	add_floats_intrinsics_128(f1, f2, f3, size);
	
	t1 = clock();

	printf("Intrinsics_128 arrays sum(%d iterations using _mm_add_ps and %d using normal sums):\n", size / 4, size - (size / 4) * 4);
	printf("=============\n");
	printf("Time: %ld\n", t1 - t0);
	printf("f[3]=%f\n", f3[7]);
	printf("t0=%ld\n", t0);
	printf("t1=%ld\n", t1);
	printf("=============\n");
	
	t0 = clock();
	
	add_floats_intrinsics_256(f1, f2, f3, size);
	
	t1 = clock();

	printf("Intrinsics_256 arrays sum(%d iterations using _mm256_add_ps and %d using normal sums):\n", size / 8, size - (size / 8) * 8);
	printf("=============\n");
	printf("Time: %ld\n", t1 - t0);
	printf("f[3]=%f\n", f3[7]);
	printf("t0=%ld\n", t0);
	printf("t1=%ld\n", t1);
	printf("=============\n");

	return 0;
}
