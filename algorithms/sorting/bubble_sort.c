#include <stdbool.h>
#include <stdio.h>

#include "array.h"
#include "sort.h"

void sort(int *arr, int *dest, int length) {
    int i, j, pivot;
    bool swapped;
	printf("bubble_sort:\n");
    if (dest) {
        copy_array(arr, dest, length);
        arr = dest;
    }
    for (i = 0; i < length - 1; i++) {
        swapped = false;
        for (j = 0; j < length - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                pivot = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = pivot;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
