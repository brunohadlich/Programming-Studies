#include <stdio.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv) {
	const int SHM_SIZE = 4096;
	char *shm_name = "shm_test";
	void *shm_ptr = NULL;
	int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0777);
	//Defines shared memory size
	ftruncate(shm_fd, SHM_SIZE);
	shm_ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	sprintf(shm_ptr, "%s", "teste");
	printf("%s", (char *)shm_ptr);
	shm_unlink(shm_name);
}
