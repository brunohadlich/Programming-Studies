#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//This example was taken from "man pipe" command
int main(int argc, char **argv) {
	int fd[2];
	//fd[0] is the reading end file descriptor
	//fd[1] is the writing end file descriptor
	pid_t childpid;
	char buf;

	if (pipe(fd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if ((childpid = fork()) == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	char teste[] = "teste\nteste2";

	if (childpid) {//childpid != 0 equals parent
		//Always close the side of the pipe that won't be used
		close(fd[0]);
		write(fd[1], teste, strlen(teste));
		//When finish writing close the file descriptor, otherwise the
		//read call on the child process will hang waiting for more data
		close(fd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	} else {//childpid == 0 equals child
		//Always close the side of the pipe that won't be used
		close(fd[1]);
		while (read(fd[0], &buf, 1) > 0) {
			write(STDOUT_FILENO, &buf, 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		close(fd[0]);
		_exit(EXIT_SUCCESS);
	}
	return 0;
}
