#include <inttypes.h>
/*
*input, a matrix of pixels rows*cols values in the range from 0..255
*output, a matrix of pixels rows*cols values in the range from 0..255
*rows, number of rows in the input and output matrixes
*cols, number of cols in the input and output matrixes
*Returns a pointer to the output matrix passed as the second argument of the function
*/
volatile void *sobel(uint8_t *input, uint8_t *output, uint16_t rows, uint16_t cols);
