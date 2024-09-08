all:
	gcc -Werror -Wall signals.c -o signals
	gcc -Werror -Wall shared_memory.c -o shared_memory -lrt
	gcc -Werror -Wall semaphores.c -o semaphores -lpthread
	gcc -Werror -Wall pipe.c -o pipe
	gcc -Werror -Wall named_pipe.c -o named_pipe
	gcc -Werror -Wall message_queue.c -o message_queue
clean:
	rm -f signals shared_memory semaphores pipe named_pipe message_queue
