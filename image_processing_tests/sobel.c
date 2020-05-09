#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#include "sobel.h"

void print_bits(uint16_t value) {
	int i;
	printf("\n");
	for (i = 63; i >= 0; i--) {
		printf("%lu", (((uint64_t)pow(2, (double)i))&value)>>i);
	}
	printf("\n");
}

/*
*input, a matrix of pixels rows*cols values in the range from 0..255
*output, a matrix of pixels rows*cols values in the range from 0..255
*rows, number of rows in the input and output matrixes
*cols, number of cols in the input and output matrixes
*/
volatile void *sobel(uint8_t *input, uint8_t *output, uint16_t rows, uint16_t cols) {

	int kernel_x[] = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};

	int kernel_y[] = {
		-1, -2, -1,
		0, 0, 0,
		1, 2, 1
	};

	int r, c;

	for (r = 1; r < rows - 1; r++) {
		for (c = 1; c < cols - 1; c++) {
			int a, b;
			int gx, gy;
			gx = gy = 0;
			int kernel_idx = 0;
			for (a = 0; a < 3; a++) {
				for (b = 0; b < 3; b++) {
					int input_idx = ((r - 1 + a) * cols + c - 1) + b;
					int input_value = input[input_idx];
					gx += input_value * kernel_x[kernel_idx];
					gy += input_value * kernel_y[kernel_idx];
					kernel_idx++;//int kernel_idx = a * 3 + b;
				}
			}
			output[r * cols + c] = sqrt(gx * gx + gy * gy);
		}
	}
}

/*
	for (r = 1; r < rows - 1; r++) {
		for (c = 1; c < cols - 1; c++) {
			int gx, gy;
			gx = gy = 0;
			gx =	-1 * input[(r - 1) * cols + (c - 1)] +1 * input[(r - 1) * cols + (c + 1)] + 
				-2 * input[(r)     * cols + (c - 1)] +2 * input[(r)     * cols + (c + 1)] +
				-1 * input[(r + 1) * cols + (c - 1)] +1 * input[(r + 1) * cols + (c + 1)];

			gy =	-1 * input[(r - 1) * cols + (c - 1)] -2 * input[(r - 1) * cols + (c)] - 1*input[(r - 1) * cols + (c + 1)] 
				+1 * input[(r + 1) * cols + (c - 1)] +2 * input[(r + 1) * cols + (c)] + 1*input[(r + 1) * cols + (c + 1)];
			output[r * cols + c] = sqrt(gx * gx + gy * gy);
		}
	}
*/
/*
	for (r = 1; r < rows - 1; r++) {
		int r_times_col = r * cols;
		int r_minus_one_times_col = r_times_col - cols;
		int r_plus_one_times_col = r_times_col + cols;
		for (c = 1; c < cols - 1; c++) {
			int gx, gy;
			gx = gy = 0;
			int c_minus_one = c - 1;
			int c_plus_one = c + 1;
			int input_r_minus_one_times_col_plus_c_minus_one	= -input[r_minus_one_times_col + c_minus_one];
			int input_r_plus_one_times_col_plus_c_plus_one		= input[r_plus_one_times_col + c_plus_one];
			int input_r_minus_one_times_col_plus_c_plus_one		= input[r_minus_one_times_col	 + c_plus_one];
			int input_r_plus_one_times_col_plus_c_minus_one		= input[r_plus_one_times_col	 + c_minus_one];
			gx =	input_r_minus_one_times_col_plus_c_minus_one	+		 input_r_minus_one_times_col_plus_c_plus_one + 
						-(input[r_times_col	+ c_minus_one]<<1)				+ (input[r_times_col + c_plus_one]<<1) +
						-input_r_plus_one_times_col_plus_c_minus_one	+ 	 input_r_plus_one_times_col_plus_c_plus_one;
			//<<1 == *2
			gy =	input_r_minus_one_times_col_plus_c_minus_one -(input[r_minus_one_times_col	+ c]<<1) - input_r_minus_one_times_col_plus_c_plus_one 
						+input_r_plus_one_times_col_plus_c_minus_one +(input[r_plus_one_times_col	+ c]<<1) + input_r_plus_one_times_col_plus_c_plus_one;
			output[r_times_col + c] = sqrt(gx * gx + gy * gy);
		}
	}
}
*/
