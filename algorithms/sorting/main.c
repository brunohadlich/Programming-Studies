#include <stdlib.h>

#include "array.h"
#include "sort.h"

int main(int argc, char *argv[]) {
    int arr[] = { 4, 2, 3, 5, 6, 1, 9, 7, 8 };
	int length = sizeof(arr) / sizeof(int);
	sort(arr, NULL, length);
	print_array(arr, length);
	return 0;
}
