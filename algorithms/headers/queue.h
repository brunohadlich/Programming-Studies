#ifndef QUEUE_H
#define QUEUE_H

typedef node_t {
	void *element;
	struct node_t next;
} Node;

typedef struct queue_t {
	Node *first;
	long length;
} Queue;

Queue *new_q();
delete_q(Queue *queue);
int enqueue_q(Queue *queue, void *element);
void *dequeue_q(Queue *queue);

#endif
