#include <syslog.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int a;
	int *b = &a;
	free(b);
	return 0;
}
