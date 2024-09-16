#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "sort.h"

void merge(int *array, int p, int q, int r) {
	int *aux_array = (int *)malloc(sizeof(int) * (r - p + 1));
	int i, j, k;
	for (i = p, j = q + 1, k = 0; i <= q && j <= r; k++) {
		if (array[i] < array[j]) {
			aux_array[k] = array[i];
			i++;
		} else {
			aux_array[k] = array[j];
			j++;
		}
	}
	for (; i <= q; i++) {
		aux_array[k] = array[i];
		k++;
	}
	for (; j <= r; j++) {
		aux_array[k] = array[j];
		k++;
	}
	for (i = 0; i < (r - p + 1); i++) {
		array[p + i] = aux_array[i];
	}
	free(aux_array);
}

void single_thread_merge_sort(int *array, int p, int r) {
	int middle;
	if (p < r) {
		middle = ((p + r) / 2);
		single_thread_merge_sort(array, p, middle);
		single_thread_merge_sort(array, middle + 1, r);
		merge(array, p, middle, r);
	}
}

void sort(int *arr, int *dest, int length) {
    int i, j, pivot;
    printf("merge_sort:\n");
    if (dest) {
        copy_array(arr, dest, length);
        arr = dest;
    }
    single_thread_merge_sort(arr, 0, length - 1);
}