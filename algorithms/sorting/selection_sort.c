#include <stdio.h>
#include <stdlib.h>

int *sort(int *arr, int length) {
	int i, j;
	for (i = 0; i < length; i++) {
		int lowest = arr[i];
		int lowest_idx = i;
		for (j = i + 1; j < length; j++) {
			if (arr[j] < lowest) {
				lowest = arr[j];
				lowest_idx = j;
			}
		}
		arr[lowest_idx] = arr[i];
		arr[i] = lowest;
	}
	return arr;
}

int main(int argc, char *argv[]) {
       	int arr[] = {1, 2, 5, 4, 3, 9, 8, 6, 7};
	int *arr2 = sort(arr, 9);
	int i;
	for (i = 0; i < 9; i++) {
		printf("%d\n", arr2[i]);
	}
}
