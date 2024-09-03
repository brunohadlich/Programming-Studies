#include <stdio.h>

void print_array(int *arr, int length) {
	for (int i = 0; i < length; i++) {
		printf("%d\n", arr[i]);
	}
}

void copy_array(int *arr, int *dest, int length) {
	for (int i = 0; i < length; i++) {
        dest[i] = arr[i];
	}
}
