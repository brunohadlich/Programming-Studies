#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef node_t {
	void *element;
	struct node_t next;
} Node;

typedef struct linked_list_t {
	Node *first;
	long length;
} LinkedList;

LinkedList *new_ll();
delete_ll(LinkedList *list);
int push_ll(LinkedList *list, void *element);
void *pop_ll(LinkedList *list);
void *top_ll(LinkedList *list);
int delete_index_ll(LinkedList *list, long index);
int delete_element_ll(LinkedList *list, void *element);
int get_element_index_ll(LinkedList *list, void *element);
void *get_element_at_index_ll(LinkedList *list, void *element);
int exist_element_ll(LinkedList *list, void *element);
int enqueue_ll(LinkedList *list, void *element);
void *dequeue_ll(LinkedList *list);

#endif
