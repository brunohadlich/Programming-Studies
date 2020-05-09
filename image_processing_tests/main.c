#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "sobel.h"

/*
*input, a matrix of pixels rows*cols*3 values, each col is composed by three values, R(ed), G(reen), B(lue). These values are in the range of 0..255 each.
*rows, number of rows in the input and output matrixes
*cols, number of cols in the input and output matrixes
*Returns a pointer to the input matrix passed as the first argument of the function
*/
uint8_t *set_img_green(uint8_t *input, int rows, int cols) {
	int h, w;
	for (h = 0; h < rows; h++) {
		for (w = 0; w < cols * 3; w+= 3) {//input so we have to jump three elements at a time
			int line = h * cols * 3;
			int col = w;
			int pixel_pos = line + col;
			input[pixel_pos + 0] = 0;	//red
			input[pixel_pos + 1] = 255;	//green
			input[pixel_pos + 2] = 0;	//blue
		}
	}
	return input;
}

/*
*input, a matrix of pixels rows*cols*3 values, each col is composed by three values, R(ed), G(reen), B(lue). These values are in the range of 0..255 each.
*output, a matrix of pixels rows*cols values in the range from 0..255
*rows, number of rows in the input and output matrixes
*cols, number of cols in the input and output matrixes
*Returns a pointer to the output matrix passed as the second argument of the function
*/
uint8_t *rgb_to_gray(uint8_t *input, uint8_t *output, int rows, int cols) {

	int h, w, l = 0;
	for (h = 0; h < rows; h++) {
		for (w = 0; w < cols * 3; w+= 3) {//rgb so we have to jump three elements at a time
			int line = h * cols * 3;
			int col = w;
			int pixel_pos = line + col;
			//There are three types of conversion to RGB all listed below
			//output[l] = ((input[pixel_pos + 0] * 0.2126) + (input[pixel_pos + 1] * 0.7152) + (input[pixel_pos + 2] * 0.0722));
			//output[l] = ((input[pixel_pos + 0] * 0.299)   + (input[pixel_pos + 1] * 0.587)   + (input[pixel_pos + 2] * 0.114));
			output[l] = ((input[pixel_pos + 0] * 0.2627)   + (input[pixel_pos + 1] * 0.6780)   + (input[pixel_pos + 2] * 0.0593));
			l++;
		}
	}
	return output;
}

const char* img_name = "images/lena_gray.bmp";
//const char* img_name = "images/Full_HD_1920x1080.bmp";
//const char* img_name = "images/4k_3840x2160.jpg";
//const char* img_name = "images/8k_7680x4320.jpg";
//const char* img_name = "images/16k_15360x8640.jpg";
//const char* img_name = "images/21600x21600.jpg";

int main(int argc, char **argv) {
	int cols, rows, bpp;
	uint8_t *img = stbi_load(img_name, &cols, &rows, &bpp, 3);
	if (img == NULL) {
		printf("Failed to read image '%s'.\n", img_name);
		return 1;
	}
	printf("channels: %d.\n", bpp);
	uint8_t *gray_scale_img;
	if (bpp == 3) {
		gray_scale_img = (uint8_t *)malloc(rows * cols * sizeof(uint8_t));
		rgb_to_gray(img, gray_scale_img, rows, cols);
		stbi_image_free(img);
	} else {
		gray_scale_img = img;
	}
	uint8_t *sob = (uint8_t *)malloc(sizeof(uint8_t) * cols * rows);
	clock_t t0 = clock();
	sobel(gray_scale_img, sob, rows, cols);
	clock_t t1 = clock();
	printf("%f\n", ((double) (t1 - t0)) / CLOCKS_PER_SEC);
	stbi_write_bmp("images/img_mod.bmp", cols, rows, 1, sob);//The 1 is the number of channels, if it was a RGB image would be three
	stbi_image_free(gray_scale_img);
	exit(0);
	return 0;
}
