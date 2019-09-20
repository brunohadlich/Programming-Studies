#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sig_handler(int sig_code) {
	if (sig_code == SIGINT) {
		printf("Caught SIGINT\n");
	} else if (sig_code == SIGSTOP) {
		printf("Caught SIGSTOP\n");
	} else if (sig_code == SIGKILL) {
		printf("Caught SIGKILL\n");
	} else if (sig_code == SIGUSR1) {
		printf("Caught SIGUSR1\n");
	}
}

int main(int argc, char *argv[]) {
	if (signal(SIGSTOP, sig_handler) == SIG_ERR) {
		printf("Could not register SIGSTOP because it is handled by the kernel and there is nothing a process can do about it.\n");
	}
	if (signal(SIGKILL, sig_handler) == SIG_ERR) {
		printf("Could not register SIGKILL because it is handled by the kernel and there is nothing a process can do about it.\n");
	}
	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		printf("Could not register SIGINT handler, something went wrong.\n");
	}
	if (signal(SIGUSR1, sig_handler) == SIG_ERR) {
		printf("Could not register SIGUSR1 handler, something went wrong.\n");
	}
	sleep(1000000);
	exit(EXIT_SUCCESS);
}
