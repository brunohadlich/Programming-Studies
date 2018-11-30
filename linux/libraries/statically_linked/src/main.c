#include <stdio.h>
#include "operations.h"

int main() {
	printf("2 + 3 = %d\n", add(2, 3));
	printf("2 - 3 = %d\n", subtract(2, 3));
	printf("2 * 3 = %d\n", multiply(2, 3));
	printf("2 / 3 = %d\n", divide(2, 3));
	return 0;
}
