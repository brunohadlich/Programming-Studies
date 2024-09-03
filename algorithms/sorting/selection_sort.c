#include <stdio.h>

#include "array.h"

void sort(int *arr, int *dest, int length) {
	int i, j, lowest, lowest_idx;
	printf("selection_sort:\n");
    if (dest) {
        copy_array(arr, dest, length);
        arr = dest;
    }
	for (i = 0; i < length; i++) {
		lowest = arr[i];
		lowest_idx = i;
		for (j = i + 1; j < length; j++) {
			if (arr[j] < lowest) {
				lowest = arr[j];
				lowest_idx = j;
			}
		}
		arr[lowest_idx] = arr[i];
		arr[i] = lowest;
	}
}
