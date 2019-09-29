/*
 * =====================================================================================
 *
 *       Filename:  avl.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/25/2019 07:49:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

struct node {
	int height;
	struct node *parent;
	struct node *left;
	struct node *right;
	int value;
};

int exists(struct node *tree, int value);
int delete(struct node *tree, int value);
int insert(struct node *tree, int value);
