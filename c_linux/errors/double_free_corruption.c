#include <syslog.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int *toosmall = malloc (100);
	free(toosmall);
	free(toosmall);
	return 0;
}
