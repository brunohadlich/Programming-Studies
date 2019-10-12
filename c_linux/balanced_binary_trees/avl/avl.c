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
#include "utils.h"
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

struct node *rotate_left(struct node *tree) {
	printf("\nBefore rotate node of value %d left:\n", tree -> value);
	printf("\n===================\n");
	breadth_first_search(tree);
	printf("\n===================\n");
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

	printf("\nAfter rotate node of value %d left:\n", tree -> value);
	printf("\n===================\n");
	breadth_first_search(pivot2);
	printf("\n===================\n");
	return pivot2;
}

struct node *rotate_right(struct node *tree) {
	printf("\nBefore rotate node of value %d right:\n", tree -> value);
	printf("\n===================\n");
	breadth_first_search(tree);
	printf("\n===================\n");
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

	printf("\nAfter rotate node of value %d right:\n", tree -> value);
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
		}
		return rotate_right(tree);
	} else if (difference < -1) {//right-height weighted
		if (value < tree -> right -> value) {
			tree -> right = rotate_right(tree -> right);
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
	int h1 = 0, h2 = 0;
	if (tree -> left) {
		h1 = depth(tree -> left, height + 1);
	}
	if (tree -> right) {
		h2 = depth(tree -> right, height + 1);
	}

	return (h1 > h2 ? h1 : h2) + 1;
}

int main() {
	FILE *default_fd = stdout;
	stdout = fopen("/dev/null", "w");

	struct node *tree = insert(NULL, 1);
	printf("\n===================\n");
	breadth_first_search(tree);
	printf("\n===================\n");

	int i;
	for (i = 2; i < 50000; i++) {
		tree = insert(tree, i);
		printf("\n===================\n");
		breadth_first_search(tree);
		printf("\n===================\n");
	}

	breadth_first_search(tree);

	stdout = default_fd;
	
	printf("\nTree depth: %d\n", depth(tree, 1));
}
