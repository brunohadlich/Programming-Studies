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
struct node *new_node(int value) {
	struct node *new_node = (struct node *) malloc(sizeof(struct node));
	new_node -> height = 1;
	new_node -> value = value;
	new_node -> left = NULL;
	new_node -> right = NULL;
	return new_node;
}

struct node *rotate_left(struct node *tree) {
	struct node *pivot = tree -> right -> left;
	tree -> right -> left = tree;
	tree -> right -> height++;
	tree -> height--;
	tree -> right = pivot;
	return tree -> right;
}

struct node *rotate_right(struct node *tree) {
	struct node *pivot = tree -> left -> right;
	tree -> left -> right = tree;
	tree -> left -> height++;
	tree -> height--;
	tree -> left = pivot;
	return tree -> left;
}

struct node *insert(struct node *tree, int value) {
	if (tree) {
		if (value <= tree -> value) {
			if (tree -> left) {
				tree -> left = insert(tree -> left, value);
			} else {
				tree -> left = new_node(value);
				return tree;
			}
		} else {
			if (tree -> right) {
				tree -> right = insert(tree -> right, value);
			} else {
				tree -> right = new_node(value);
				return tree;
			}
		}
		printf("value: %d\n", value);

		int left_height = 0, right_height = 0;

		if (tree -> left) {
			left_height = tree -> left -> height;
			if (tree -> left -> height == tree -> height) {
				tree -> height = tree -> left -> height + 1;
			}
		}

		if (tree -> right) {
			right_height = tree -> right -> height;
			if (tree -> right -> height >= tree -> height) {
				tree -> height = tree -> right -> height + 1;
			}
		}

		int difference = left_height - right_height;
		printf("difference: %d\n", difference);

		if (difference > 1) {//left-height weighted
			if (value > tree -> left -> value) {
				tree -> left = rotate_left(tree -> left);
			}
			return rotate_right(tree);
		} else if (difference < -1) {//right-height weighted
			if (value < tree -> right -> value) {
				tree -> right = rotate_right(tree -> right);
			}
			return rotate_left(tree);
		}

		return tree;
	} else {
		return new_node(value);
	}
}

int depth(struct node *tree) {
	int result = 0;
	for (; tree; result++, tree = tree -> left);
	return result;
}

void inorder(struct node *tree) {
	printf("%d\n", tree -> value);
	if (tree -> left) {
		inorder(tree -> left);
	}
	if (tree -> right) {
		inorder(tree -> right);
	}
}

int main() {
	struct node *tree = insert(NULL, 1);
	insert(tree, 2);
	insert(tree, 3);
	insert(tree, 4);
	insert(tree, 5);
	insert(tree, 6);
	insert(tree, 7);
	insert(tree, 8);
	insert(tree, 9);
	inorder(tree);

	//printf("root height: %d", tree -> height);
	//printf("depth: %d", depth2(tree));
}
