#include <syslog.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int a;
	int *b = &a;
	// Trying to free a pointer which address belongs to the stack
	free(b);
	return 0;
}
