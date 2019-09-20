#include <mqueue.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

int main(int argc, char **argv) {
	const char *server_queue_name = "/server_queue";
	const int perm = 0777;
	mqd_t server_mqd;
	struct mq_attr attr;
	struct timespec t;
	time_t sec = time(NULL);

	//both tv_sec and tv_nsec must be set otherwise they can have invalid values causing unexpected behavior
	t.tv_sec = sec + 3;
	t.tv_nsec = 0;

	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 256;
	attr.mq_curmsgs = 0;

	if ((server_mqd = mq_open(server_queue_name, O_RDWR | O_CREAT, perm, &attr)) == -1) {
		perror("mq_open: ");
		switch(errno) {
			case EACCES:
				printf("EACCESS\n");
				break;
			case EEXIST:
				printf("EEXIST\n");
				break;
			case EINVAL:
				printf("EINVAL\n");
				break;
			case EMFILE:
				printf("EMFILE\n");
				break;
			case ENAMETOOLONG:
				printf("ENAMETOOLONG\n");
				break;
			case ENFILE:
				printf("ENFILE\n");
				break;
			case ENOENT:
				printf("ENOENT\n");
				break;
			case ENOMEM:
				printf("ENOMEM\n");
				break;
			case ENOSPC:
				printf("ENOSPC\n");
				break;
			default:
				printf("unknown error\n");
		}
		exit(1);
	}

	const char *msg_write = "testando message queue";
	char msg_read[attr.mq_msgsize];

	int i;

	for (i = 0; i < 5; i++) {
		unsigned int k = rand() % 20;
		if (mq_send(server_mqd, msg_write, strlen(msg_write) + 1, k) == -1) {
			printf("mq_send error\n");
		}
		printf("sent message '%s' with priotiry '%d'\n", msg_write, k);
		k = rand() % 20;
		if (mq_timedsend(server_mqd, msg_write, strlen(msg_write) + 1, k, &t) == -1) {
			printf("mq_timedsend error\n");
		}
		printf("sent message '%s' with priotiry '%d'\n", msg_write, k);
	}

	unsigned int msg_prio = 999999;

	msg_prio = 999999;

	int ret;

	for (i = 0; i < 5; i++) {
		if ((ret = mq_timedreceive(server_mqd, msg_read, attr.mq_msgsize, &msg_prio, &t)) == -1) {
			perror("mq_timedreceive");
			switch(errno) {
				case EAGAIN:
					printf("EAGAIN\n");
					break;
				case EBADF:
					printf("EBADF\n");
					break;
				case EINTR:
					printf("EINTR\n");
					break;
				case EINVAL:
					printf("EINVAL\n");
					break;
				case EMSGSIZE:
					printf("EMSGSIZE\n");
					break;
				case ETIMEDOUT:
					printf("ETIMEDOUT\n");
					break;
				default:
					printf("unknown error\n");
			}
			exit(1);
		}

		printf("received message '%s' of priority %d\n", msg_read, msg_prio);

		mq_receive(server_mqd, msg_read, attr.mq_msgsize, &msg_prio);

		printf("received message '%s' of priority %d\n", msg_read, msg_prio);
	}

	mq_close(server_mqd);
	mq_unlink(server_queue_name);

	return EXIT_SUCCESS;
}
