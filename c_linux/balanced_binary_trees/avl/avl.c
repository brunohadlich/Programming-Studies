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
struct node *new_node(struct node *parent, int value) {
	struct node *new_node = (struct node *) malloc(sizeof(struct node));
	new_node -> height = 1;
	new_node -> value = value;
	new_node -> left = NULL;
	new_node -> right = NULL;
	return new_node;
}

void rotate_left(struct node *tree) {
	struct node *pivot = tree -> right -> left;
	tree -> right -> left = tree;
	tree -> right -> height += 1;
	tree -> right = pivot;
	tree -> height -= 1;
}

int insert(struct node *tree, int value) {
	if (tree) {
		if (value <= tree -> value) {
			if (tree -> left) {
				insert(tree -> left, value);
			}
			struct node *child = new_node(tree, value);
			tree -> left = child;
		} else {
			if (tree -> right) {
				insert(tree -> right, value);
			} else {
				struct node *child = new_node(tree, value);
				tree -> right = child;
			}
		}

		int left_height, right_height;

		if (tree -> left) {
			left_height = tree -> left -> height;
			if (tree -> left -> height + 1 > tree -> height) {
				tree -> height = tree -> left -> height + 1;
			}
		} else {
			left_height = 0;
		}

		if (tree -> right) {
			right_height = tree -> right -> height;
			if (tree -> right -> height + 1 > tree -> height) {
				tree -> height = tree -> right -> height + 1;
			}
		} else {
			right_height = 0;
		}

		int difference = left_height - right_height;

		if (difference > 1) {//left-height weighted
			if (value > tree -> left -> value) {
				rotate_left(tree -> left);
			}
			rotate_right(tree);
		} else if (difference < -1) {//right-height weighted
			if (value < tree -> right -> value) {
				rotate_right(tree -> right);
			}
			rotate_left(tree);
		}

		return 1;
	}
	return 0;
}

int main() {
	struct node *tree = new_node(NULL, 1);
	insert(tree, 2);
	insert(tree, 3);
	insert(tree, 4);
	insert(tree, 5);
	insert(tree, 6);
	insert(tree, 7);
	insert(tree, 8);
	insert(tree, 9);
	printf("root height: %d", tree -> height);
}
