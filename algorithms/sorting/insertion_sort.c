#include <stdio.h>

#include "array.h"

void sort(int *arr, int *dest, int length) {
	int i, j, key;
	printf("insertion_sort:\n");
    if (dest) {
        copy_array(arr, dest, length);
        arr = dest;
    }
	for (i = 1; i < length; i++) {
		key = arr[i];
		for (j = i - 1; j >= 0 && arr[j] > key; j--) {
			arr[j+1] = arr[j];
		}
		arr[j + 1] = key;
	}
}
