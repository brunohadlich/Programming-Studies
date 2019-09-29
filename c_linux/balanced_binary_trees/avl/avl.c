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
	new_node -> parent = parent;
	new_node -> value = value;
	new_node -> left = NULL;
	new_node -> right = NULL;
	return new_node;
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
		if (tree -> left && tree -> left -> height + 1 > tree -> height) {
			tree -> height = tree -> left -> height + 1;
		}
		if (tree -> right && tree -> right -> height + 1 > tree -> height) {
			tree -> height = tree -> right -> height + 1;
		}

		int difference = tree -> left -> height - tree -> right -> height;

		if (difference > 1) {
			rotate_right(tree);
		} else if (difference < -1) {
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
	printf("root height: %d", tree -> height);
}
