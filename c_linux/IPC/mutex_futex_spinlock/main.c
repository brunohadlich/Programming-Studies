#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;

int main(int argc, char *argv[]) {
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
}
