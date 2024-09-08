#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "merge_sort.h"
#include "utils.h"

void test_and_benchmark_n_elements(int n) {
	const int SEED = 1;
	int *array = make_array(n);
	fill_array_random(array, n, SEED);
	clock_t t0 = clock();
	merge_sort(array, n);
	clock_t t1 = clock();
	if (!is_sorted(array, n)) {
		int i;
		int last = -1;
		for (i = 0; i < n; i++) {
			if (last > array[i]) {
				printf("\nSorting array of size %d failed at index %d.\n", n, i);
				exit(1);
			}
			last = array[i];
		}
	}
	free(array);
}

int main() {
	test_and_benchmark_n_elements(10);
	test_and_benchmark_n_elements(101);
	test_and_benchmark_n_elements(102);
	test_and_benchmark_n_elements(103);
	test_and_benchmark_n_elements(104);
	test_and_benchmark_n_elements(105);
	test_and_benchmark_n_elements(106);
	test_and_benchmark_n_elements(107);
	test_and_benchmark_n_elements(108);
	test_and_benchmark_n_elements(100);
	test_and_benchmark_n_elements(1000);
	test_and_benchmark_n_elements(1013);
	test_and_benchmark_n_elements(1777);
	test_and_benchmark_n_elements(1701);
	test_and_benchmark_n_elements(1246);
	test_and_benchmark_n_elements(10000);
	test_and_benchmark_n_elements(13001);
	test_and_benchmark_n_elements(14137);
	test_and_benchmark_n_elements(15622);
	test_and_benchmark_n_elements(19766);
	test_and_benchmark_n_elements(100000);
	test_and_benchmark_n_elements(1000000);
	test_and_benchmark_n_elements(10000000);
	printf("Tests executed with success!\n");
}
