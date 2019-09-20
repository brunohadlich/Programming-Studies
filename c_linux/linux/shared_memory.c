#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
	const int SHM_SIZE = 4096;
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;
	char *shm_name = "shm_test";
	void *shm_ptr = NULL;
	//Created the shared memory file descriptor
	int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0777);
	if (shm_fd == -1) {
		perror("shm_open failed to create shared memory file descriptor.");
		exit(EXIT_FAILURE);
	}
	//Defines shared memory size, by default it is 0 so we extend it with ftruncate
	if (ftruncate(shm_fd, SHM_SIZE) == -1) {
		perror("ftruncate failed to extend shared memory size.");
		exit(EXIT_FAILURE);
	}
	//Maps file descriptor to memory region
	shm_ptr = mmap(NULL, SHM_SIZE, protection, visibility, shm_fd, 0);
	if (shm_ptr == MAP_FAILED) {
		perror("mmap failed to map shared memory file descriptor to RAM.");
		exit(EXIT_FAILURE);
	}
	sprintf(shm_ptr, "%s", "teste");
	printf("%s", (char *)shm_ptr);
	if (munmap(shm_ptr, SHM_SIZE) == -1) {
		perror("munmap failed to unmap the shared memory.");
		exit(EXIT_FAILURE);
	}
	if (shm_unlink(shm_name) == -1) {
		perror("shm_unlink failed to unlink the shared memory.");
		exit(EXIT_FAILURE);
	}
	sleep(999999);
}
