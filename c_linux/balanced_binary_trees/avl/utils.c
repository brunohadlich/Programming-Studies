/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/10/2019 09:45:31 PM
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
#include "utils.h"

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
	printf("\n%d", tree -> value);
	if (tree -> left) {
		print_values_preorder(tree -> left, depth + 1);
	}
	if (tree -> right) {
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

struct node *new_node(int value) {
	struct node *new_node = (struct node *) malloc(sizeof(struct node));
	new_node -> height = 1;
	new_node -> value = value;
	new_node -> left = NULL;
	new_node -> right = NULL;
	return new_node;
}

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
