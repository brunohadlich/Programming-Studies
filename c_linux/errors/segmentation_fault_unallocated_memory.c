#include <stdlib.h>
#include <stdio.h>

int main() {
	int *int_ptr = (int *)malloc(sizeof(int));
	*int_ptr = 4;
	printf("%d\n", *int_ptr);
	free(int_ptr);
	// After int_ptr got freed it became a dangling pointer.
	// From now on two things may happen:
	//
	// 1 - The block of memory starting in int_ptr can be
	// given to another malloc inside this process causing
	// unexpected values in int_ptr, when dereferenced.
	//
	// 2 - The memory that once belonged to this process
	// will be allocated to another process causing a
	// segmentation fault.
}
