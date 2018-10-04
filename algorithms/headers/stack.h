#ifndef STACK_H
#define STACK_H

typedef node_t {
	void *element;
	struct node_t next;
} Node;

typedef struct stack_t {
	Node *top;
	long length;
} Stack;

Stack *new_s();
delete_s(Stack *stack);
int push_s(Stack *stack, void *element);
void *pop_s(Stack *stack);
void *top_s(Stack *stack);

#endif
