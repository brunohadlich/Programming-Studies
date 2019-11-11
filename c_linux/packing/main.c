/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/11/2019 07:07:41 PM
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

struct s1 {
	long double v1;
	char v2;
	long double v3;
	char v4;
	long double v5;
	char v6;
	long double v7;
	char v8;
};

struct s2 {
	long double v1;
	long double v3;
	long double v5;
	long double v7;
	char v2;
	char v4;
	char v6;
	char v8;
};

int main() {
	printf("long double: %lu\n", sizeof(long double));
	printf("struct s1: %lu\n", sizeof(struct s1));
	printf("struct s2: %lu\n", sizeof(struct s2));
}
