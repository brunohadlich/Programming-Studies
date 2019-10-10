/*
 * =====================================================================================
 *
 *       Filename:  avl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/27/2019 07:28:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int exists(struct node *tree, int value) {
	if (tree) {
		if (tree -> value == value) {
			return 1;
		}
		if (tree -> value > value) {
			return exists(tree -> left, value);
		} else if (tree -> value < value) {
			return exists(tree -> right, value);
		}
	}
	return 0;
}

/*
int delete(struct node *tree, int value) {
	if (tree) {
		if (tree -> value == value) {
			return 1;
		}
		if (tree -> value > value) {
			return delete(tree -> left, value);
		} else if (tree -> value < value) {
			return delete(tree -> right, value);
		}
	}
	return 0;
}
*/
struct node *new_node(int value) {
	struct node *new_node = (struct node *) malloc(sizeof(struct node));
	new_node -> height = 1;
	new_node -> value = value;
	new_node -> left = NULL;
	new_node -> right = NULL;
	return new_node;
}

struct node *rotate_left(struct node *tree) {
	printf("\nBefore rotate left:\n");
	printf("\n===================\n");
	breadth_first_search(tree);
	printf("\n===================\n");
	printf("\nrotating left: %d", tree -> value);
	struct node *pivot = tree -> right -> left;
	tree -> right -> left = tree;
	struct node *pivot2 = tree -> right;
	tree -> right = pivot;


	int greater = -2;
	if (tree -> right && tree -> right -> height > greater) {
		greater = tree -> right -> height;
	}
	if (tree -> left && tree -> left -> height > greater) {
		greater = tree -> left -> height;
	}
	if (greater == -2) {
		tree -> height = 1;
	} else  {
		tree -> height = greater + 1;
	}
	greater = -2;
	if (pivot2 -> right && pivot2 -> right -> height > greater) {
		greater = pivot2 -> right -> height;
	}
	if (pivot2 -> left && pivot2 -> left -> height > greater) {
		greater = pivot2 -> left -> height;
	}
	pivot2 -> height = greater + 1;


	printf("\nAfter rotate left:\n");
	printf("\n===================\n");
	breadth_first_search(pivot2);
	printf("\n===================\n");
	return pivot2;
}

struct node *rotate_right(struct node *tree) {
	printf("\nBefore rotate right:\n");
	printf("\n===================\n");
	breadth_first_search(tree);
	printf("\n===================\n");
	printf("\nrotating right: %d", tree -> value);
	struct node *pivot = tree -> left -> right;
	tree -> left -> right = tree;
	struct node *pivot2 = tree -> left;
	tree -> left = pivot;

	int greater = -2;
	if (tree -> right && tree -> right -> height > greater) {
		greater = tree -> right -> height;
	}
	if (tree -> left && tree -> left -> height > greater) {
		greater = tree -> left -> height;
	}
	if (greater == -2) {
		tree -> height = 1;
	} else  {
		tree -> height = greater + 1;
	}
	greater = -2;
	if (pivot2 -> right && pivot2 -> right -> height > greater) {
		greater = pivot2 -> right -> height;
	}
	if (pivot2 -> left && pivot2 -> left -> height > greater) {
		greater = pivot2 -> left -> height;
	}
	pivot2 -> height = greater + 1;

	printf("\nAfter rotate right:\n");
	printf("\n===================\n");
	breadth_first_search(pivot2);
	printf("\n===================\n");
	return pivot2;
}

int get_difference(struct node *tree) {
	int left_height = 0, right_height = 0;

	if (tree -> left) {
		left_height = tree -> left -> height;
		if (tree -> left -> height >= tree -> height) {
			tree -> height = tree -> left -> height + 1;
		}
	}

	if (tree -> right) {
		right_height = tree -> right -> height;
		if (tree -> right -> height >= tree -> height) {
			tree -> height = tree -> right -> height + 1;
		}
	}

	return left_height - right_height;
}

struct node *balance(int value, struct node *tree) {
	int difference = get_difference(tree);
	if (difference > 1) {//left-height weighted
		if (value > tree -> left -> value) {
			tree -> left = rotate_left(tree -> left);
			//tree = rotate_left(tree -> left);
		}
		return rotate_right(tree);
	} else if (difference < -1) {//right-height weighted
		if (value < tree -> right -> value) {
			tree -> right = rotate_right(tree -> right);
			//tree = rotate_right(tree -> right);
		}
		return rotate_left(tree);
	}
	return tree;
}

struct node *insert(struct node *tree, int value) {
	if (tree) {
		if (value <= tree -> value) {
			tree -> left = tree -> left ? insert(tree -> left, value) : new_node(value);
		} else {
			tree -> right = tree -> right ? insert(tree -> right, value) : new_node(value);
		}
		return balance(value, tree);
	} else {
		return new_node(value);
	}
}

int depth(struct node *tree, int height) {
	printf("\nvalue: %d, height: %d", tree -> value, height);
	int h1 = 0, h2 = 0;
	if (tree -> left) {
		h1 = depth(tree -> left, height + 1);
	}
	if (tree -> right) {
		h2 = depth(tree -> right, height + 1);
	}

	return (h1 > h2 ? h1 : h2) + 1;
}

void print_values_inorder(struct node *tree) {
	if (tree -> left) {
		print_values_inorder(tree -> left);
	}
	printf("\n%d", tree -> value);
	if (tree -> right) {
		print_values_inorder(tree -> right);
	}
}

void print_values_preorder(struct node *tree, int depth) {
	printf("depth: %d, value: %d", depth, tree -> value);
	if (tree -> left) {
		printf("\nleft, ");
		print_values_preorder(tree -> left, depth + 1);
	}
	if (tree -> right) {
		printf("\nright, ");
		print_values_preorder(tree -> right, depth + 1);
	}
}

void print_values_postorder(struct node *tree) {
	if (tree -> left) {
		print_values_postorder(tree -> left);
	}
	if (tree -> right) {
		print_values_postorder(tree -> right);
	}
	printf("\n%d", tree -> value);
}

struct queue_element {
	int depth;
	struct node *element;
	struct queue_element *next;
};

struct queue {
	struct queue_element *first;
	struct queue_element *last;
};

void breadth_first_search(struct node *tree) {
	struct queue q;
	q.first = (struct queue_element *)malloc(sizeof(struct queue_element));
	q.first -> depth = 1;
	q.first -> element = tree;
	q.first -> next = NULL;
	q.last = q.first; 
	while(q.first != NULL) {
		struct queue_element *f = q.first;
		printf("\nlevel %d, value %d, height %d", f -> depth, f -> element -> value, f -> element -> height);
		if (f -> element -> left) {
			struct queue_element *new = (struct queue_element *)malloc(sizeof(struct queue_element));
			new -> depth = f -> depth + 1;
			new -> element = f -> element -> left;
			new -> next = NULL;
			q.last -> next = new;
			q.last = new;
		}
		if (f -> element -> right) {
			struct queue_element *new = (struct queue_element *)malloc(sizeof(struct queue_element));
			new -> depth = f -> depth + 1;
			new -> element = f -> element -> right;
			new -> next = NULL;
			q.last -> next = new;
			q.last = new;
		}
		q.first = f -> next;
	}
}

int main() {
	struct node *tree = insert(NULL, 1);
	int i;
	for (i = 13; i < 25; i++) {
		printf("\n===================\n");
		breadth_first_search(tree);
		printf("\n===================\n");
		tree = insert(tree, i);
	}

	for (i = 2; i < 13; i++) {
		printf("\n===================\n");
		breadth_first_search(tree);
		printf("\n===================\n");
		tree = insert(tree, i);
	}
	printf("\n===================\n");
	breadth_first_search(tree);
	printf("\n===================\n");

	/*

	for (i = 25; i < 50; i++) {
		tree = insert(tree, i);
	}



	for (i = 85; i < 120; i++) {
		tree = insert(tree, i);
	}
	*/
	printf("\n");
	print_values_preorder(tree, 1);
	//print_values_inorder(tree);
	//print_values_postorder(tree);

	printf("\nroot height: %d", tree -> height);
	printf("\ndepth: %d", depth(tree, 1));
}
