#include <stdlib.h>
#include <stdio.h>

int main() {
	fwrite("Hello, world!\n", 1, sizeof("Hello, world!\n"), stdout);
	exit(0);
}
