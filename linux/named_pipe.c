#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	char *myfifo = "/tmp/myfifo";
	char arr1[80], arr2[80];
	int fd;

	if (mkfifo(myfifo, 0666)) {
		perror("mkfifo");
	}

	while(1) {
		fd = open(myfifo, O_WRONLY);

		fgets(arr2, 80, stdin);

		write(fd, arr2, strlen(arr2) + 1);

		printf("Wrote '%s' to pipe '%s'", arr2, myfifo);

		close(fd);

		fd = open(myfifo, O_RDONLY);

		read(fd, arr1, sizeof(arr1));

		printf("Read '%s' from pipe '%s'", arr1, myfifo);

		close(fd);
	}

	return EXIT_SUCCESS;
}
