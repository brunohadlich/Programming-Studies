#include <syslog.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int *int_ptr = malloc (sizeof(int));
	free(int_ptr);
	free(int_ptr);
	return 0;
}
