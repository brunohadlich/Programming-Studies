/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/2019 08:28:05 PM
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

struct Matrix {
	int rows;
	int cols;
	float *array;
};

typedef struct Matrix * Matrix;

Matrix new_matrix(int rows, int cols) {
	Matrix m = (Matrix)malloc(sizeof(struct Matrix));
	m -> rows = rows;
	m -> cols = cols;
	m -> array = (float *)malloc(rows * cols * sizeof(float));
	return m;
}

float at(Matrix m, int row, int col) {
	return m -> array[row * m -> cols + col];
}

float *at_(Matrix m, int row, int col) {
	return &(m -> array[row * m -> cols + col]);
}

float lowest_row_value(Matrix m, int row) {
	int i;
	float lowest = 999999;
	for (i = 0; i < m -> cols; i++) {
		float tmp = at(m, row, i);
		if (tmp < lowest) {
			lowest = tmp;
		}
	}
	return lowest;
}

float lowest_col_value(Matrix m, int col) {
	int i;
	float lowest = 999999;
	for (i = 0; i < m -> rows; i++) {
		float tmp = at(m, i, col);
		if (tmp < lowest) {
			lowest = tmp;
		}
	}
	return lowest;
}

int row_has_zero(Matrix m, int row) {
	int i;
	for (i = 0; i < m -> cols; i++) {
		if (at(m, row, i) == 0) {
			return 1;
		}
	}
	return 0;
}

int col_has_zero(Matrix m, int col) {
	int i;
	for (i = 0; i < m -> rows; i++) {
		if (at(m, i, col) == 0) {
			return 1;
		}
	}
	return 0;
}

int all_rows_have_zero(Matrix m) {
	int i;
	for (i = 0; i < m -> rows; i++) {
		if (!row_has_zero(m, i)) {
			return 0;
		}
	}
	return 1;
}

int all_cols_have_zero(Matrix m) {
	int i;
	for (i = 0; i < m -> cols; i++) {
		if (!col_has_zero(m, i)) {
			return 0;
		}
	}
	return 1;
}

void subtract_row(Matrix m, int row, float value) {
	int i;
	for (i = 0; i < m -> cols; i++) {
		*at_(m, row, i) -= value;
	}
}

void subtract_col(Matrix m, int col, float value) {
	int i;
	for (i = 0; i < m -> rows; i++) {
		*at_(m, i, col) -= value;
	}
}

void subtract_rows_minimum(Matrix m) {
	int i;
	for (i = 0; i < m-> rows; i++) {
		subtract_row(m, i, lowest_row_value(m, i));
	}
}

void subtract_cols_minimum(Matrix m) {
	int i;
	for (i = 0; i < m-> cols; i++) {
		subtract_col(m, i, lowest_col_value(m, i));
	}
}

void pass1(Matrix m) {
	if (!all_rows_have_zero(m)) {
		subtract_rows_minimum(m);
	}
}

void pass2(Matrix m) {
	if (!all_cols_have_zero(m)) {
		subtract_cols_minimum(m);
	}
}

void print_matrix(Matrix m) {
	int row, col;
	for (row = 0; row < m -> rows; row++) {
		for (col = 0; col < m -> cols; col++) {
			printf("%f ", at(m, row, col));
		}
		printf("\n");
	}
}

void example1() {
	printf("Example 1:\n");
	Matrix m = new_matrix(4, 4);
	*at_(m, 0, 0) = 5;
	*at_(m, 0, 1) = 24;
	*at_(m, 0, 2) = 13;
	*at_(m, 0, 3) = 7;
	*at_(m, 1, 0) = 10;
	*at_(m, 1, 1) = 25;
	*at_(m, 1, 2) = 3;
	*at_(m, 1, 3) = 23;
	*at_(m, 2, 0) = 28;
	*at_(m, 2, 1) = 9;
	*at_(m, 2, 2) = 8;
	*at_(m, 2, 3) = 5;
	*at_(m, 3, 0) = 10;
	*at_(m, 3, 1) = 17;
	*at_(m, 3, 2) = 15;
	*at_(m, 3, 3) = 3;

	pass1(m);
	pass2(m);
	print_matrix(m);
}

void example2() {
	printf("Example 2:\n");
	Matrix m = new_matrix(4, 4);
	*at_(m, 0, 0) = 2;
	*at_(m, 0, 1) = 1;
	*at_(m, 0, 2) = 4;
	*at_(m, 0, 3) = 2;
	*at_(m, 1, 0) = 3;
	*at_(m, 1, 1) = 4;
	*at_(m, 1, 2) = 1;
	*at_(m, 1, 3) = 6;
	*at_(m, 2, 0) = 1;
	*at_(m, 2, 1) = 2;
	*at_(m, 2, 2) = 6;
	*at_(m, 2, 3) = 5;
	*at_(m, 3, 0) = 1;
	*at_(m, 3, 1) = 3;
	*at_(m, 3, 2) = 3;
	*at_(m, 3, 3) = 7;

	pass1(m);
	pass2(m);
	print_matrix(m);
}

int main(int argc, char *argv[]) {
	example1();
	example2();

	return 0;
}
