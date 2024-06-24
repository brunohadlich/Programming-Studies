#include <stdio.h>
#include <stdlib.h>

int *sort(int *arr, int length) {
	int i, j;
	for (i = 1; i < length; i++) {
		int key = arr[i];
		for (j = i - 1; j >= 0 && arr[j] > key; j--) {
			arr[j+1] = arr[j];
		}
		arr[j + 1] = key;
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
