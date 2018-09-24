#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	int fd[2];
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

	char *teste = "teste\nteste2";

	if (childpid) {//parent
		//Sempre fechar o lado que não será usado
		close(fd[0]);//fd[0] é o descritor de leitura
		write(fd[1], teste, strlen(teste));
		close(fd[1]);//fd[1] é o descritor de escrita
		wait(NULL);
		exit(EXIT_SUCCESS);
	} else {//child
		//Sempre fechar o lado que não será usado
		close(fd[1]);
		while(read(fd[0], &buf, 1) > 0) {
			write(STDOUT_FILENO, &buf, 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		close(fd[0]);
		write(fd[1], teste, strlen(teste));
		_exit(EXIT_SUCCESS);
	}
	return 0;
}
