#include "avl.h"

struct queue_element {
	int depth;
	struct node *element;
	struct queue_element *next;
};

struct queue {
	struct queue_element *first;
	struct queue_element *last;
};

void printf_values_inorder(struct node *tree);
void printf_values_preorder(struct node *tree);
void printf_values_postorder(struct node *tree);
struct node *new_node(int value);
void breadth_first_search(struct node *tree);
