/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/19/2019 07:07:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "utils.h"

int is_sorted(int *array, int length) {
	int i;
	int last = -1;
	for (i = 0; i < length; i++) {
		if (last > array[i]) {
			return 0;
		}
		last = array[i];
	}
	return 1;
}

int *make_array(int length) {
	return (int *)malloc(sizeof(int) * length);
}

void fill_array_random(int *array, int length, int seed) {
	int i;
	if (seed == -1) {
		srand(time(0));
	} else {
		srand(seed);
	}

	for (i = 0; i < length; i++) {
		array[i] = rand();
	}
}

void print_array(int *array, int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}
