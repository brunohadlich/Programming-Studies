#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

sem_t mutex;
int i = 0;

void *foo(void *ptr) {
	while(i < 100000) {
		sem_wait(&mutex);
		i++;
		printf("thread %ld: %d\n", pthread_self(), i);
		sem_post(&mutex);
	}
}

int main(int argc, char **argv) {
	pthread_t t0, t1;
	int iret0, iret1;

	sem_init(&mutex, 0, 1);

	if ((iret0 = pthread_create(&t0, NULL, foo, NULL))) {
		printf("Failed to create thread 0, pthread_create retured: %d.", iret0);
	}

	if ((iret1 = pthread_create(&t1, NULL, foo, NULL))) {
		printf("Failed to create thread 1, pthread_create retured: %d.", iret1);
	}

	pthread_join(t0, NULL);
	pthread_join(t1, NULL);

	sem_destroy(&mutex);

	exit(EXIT_SUCCESS);
}
