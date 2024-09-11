#include <stddef.h>

int main() {
	int *foo = NULL;
	// Trying to write to NULL pointer
	*foo = 5;
}
