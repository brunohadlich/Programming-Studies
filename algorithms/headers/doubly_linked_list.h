#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

typedef struct node_t {
	void *element;
	struct node_t previous;
	struct node_t next;
} Node;

typedef struct doubly_linked_list_t {
	Node *first;
	Node *last;
	long length;
} DoublyLinkedList;

DoublyLinkedList *new_dl();
delete_dl(DoublyLinkedList *list);
int push_dl(DoublyLinkedList *list, void *element);
void *pop_dl(DoublyLinkedList *list);
void *top_dl(DoublyLinkedList *list);
int delete_index_dl(DoublyLinkedList *list, long index);
int delete_element_dl(DoublyLinkedList *list, void *element);
int get_element_index_dl(DoublyLinkedList *list, void *element);
void *get_element_at_index_dl(DoublyLinkedList *list, void *element);
int exist_element_dl(DoublyLinkedList *list, void *element);
int enqueue_dl(DoublyLinkedList *list, void *element);
void *dequeue_dl(DoublyLinkedList *list);

#endif
