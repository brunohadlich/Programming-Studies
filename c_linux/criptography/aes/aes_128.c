/*
 * =====================================================================================
 *
 *       Filename:  aes.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/18/2019 08:53:53 PM
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

struct round_key {
	unsigned char word0[4];
	unsigned char word1[4];
	unsigned char word2[4];
	unsigned char word3[4];
};

void print_word(unsigned char *word) {
	int i;
	for (i = 0; i < 4; i++) {
		printf("0x%x ", word[i] & 0xff);
	}
}

void print_key(struct round_key *key) {
	int i;
	printf("\n");
	for (i = 0; i < 4; i++) {
		print_word(&(((unsigned char *)key)[i * 4]));
	}
	printf("\n");
}

unsigned char s_box_table[256] = {
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

unsigned char table_L[256] = {
	0x00, 0x00, 0x19, 0x01, 0x32, 0x02, 0x1a, 0xc6, 0x4b, 0xc7, 0x1b, 0x68, 0x33, 0xee, 0xdf, 0x03,
	0x64, 0x04, 0xe0, 0x0e, 0x34, 0x8d, 0x81, 0xef, 0x4c, 0x71, 0x08, 0xc8, 0xf8, 0x69, 0x1c, 0xc1,
	0x7d, 0xc2, 0x1d, 0xb5, 0xf9, 0xb9, 0x27, 0x6a, 0x4d, 0xe4, 0xa6, 0x72, 0x9a, 0xc9, 0x09, 0x78,
	0x65, 0x2f, 0x8a, 0x05, 0x21, 0x0f, 0xe1, 0x24, 0x12, 0xf0, 0x82, 0x45, 0x35, 0x93, 0xda, 0x8e,
	0x96, 0x8f, 0xdb, 0xbd, 0x36, 0xd0, 0xce, 0x94, 0x13, 0x5c, 0xd2, 0xf1, 0x40, 0x46, 0x83, 0x38,
	0x66, 0xdd, 0xfd, 0x30, 0xbf, 0x06, 0x8b, 0x62, 0xb3, 0x25, 0xe2, 0x98, 0x22, 0x88, 0x91, 0x10,
	0x7e, 0x6e, 0x48, 0xc3, 0xa3, 0xb6, 0x1e, 0x42, 0x3a, 0x6b, 0x28, 0x54, 0xfa, 0x85, 0x3d, 0xba,
	0x2b, 0x79, 0x0a, 0x15, 0x9b, 0x9f, 0x5e, 0xca, 0x4e, 0xd4, 0xac, 0xe5, 0xf3, 0x73, 0xa7, 0x57,
	0xaf, 0x58, 0xa8, 0x50, 0xf4, 0xea, 0xd6, 0x74, 0x4f, 0xae, 0xe9, 0xd5, 0xe7, 0xe6, 0xad, 0xe8,
	0x2c, 0xd7, 0x75, 0x7a, 0xeb, 0x16, 0x0b, 0xf5, 0x59, 0xcb, 0x5f, 0xb0, 0x9c, 0xa9, 0x51, 0xa0,
	0x7f, 0x0c, 0xf6, 0x6f, 0x17, 0xc4, 0x49, 0xec, 0xd8, 0x43, 0x1f, 0x2d, 0xa4, 0x76, 0x7b, 0xb7,
	0xcc, 0xbb, 0x3e, 0x5a, 0xfb, 0x60, 0xb1, 0x86, 0x3b, 0x52, 0xa1, 0x6c, 0xaa, 0x55, 0x29, 0x9d,
	0x97, 0xb2, 0x87, 0x90, 0x61, 0xbe, 0xdc, 0xfc, 0xbc, 0x95, 0xcf, 0xcd, 0x37, 0x3f, 0x5b, 0xd1,
	0x53, 0x39, 0x84, 0x3c, 0x41, 0xa2, 0x6d, 0x47, 0x14, 0x2a, 0x9e, 0x5d, 0x56, 0xf2, 0xd3, 0xab,
	0x44, 0x11, 0x92, 0xd9, 0x23, 0x20, 0x2e, 0x89, 0xb4, 0x7c, 0xb8, 0x26, 0x77, 0x99, 0xe3, 0xa5,
	0x67, 0x4a, 0xed, 0xde, 0xc5, 0x31, 0xfe, 0x18, 0x0d, 0x63, 0x8c, 0x80, 0xc0, 0xf7, 0x70, 0x07
};

unsigned char table_E[256] = {
	0x01, 0x03, 0x05, 0x0f, 0x11, 0x33, 0x55, 0xff, 0x1a, 0x2e, 0x72, 0x96, 0xa1, 0xf8, 0x13, 0x35,
	0x5f, 0xe1, 0x38, 0x48, 0xd8, 0x73, 0x95, 0xa4, 0xf7, 0x02, 0x06, 0x0a, 0x1e, 0x22, 0x66, 0xaa,
	0xe5, 0x34, 0x5c, 0xe4, 0x37, 0x59, 0xeb, 0x26, 0x6a, 0xbe, 0xd9, 0x70, 0x90, 0xab, 0xe6, 0x31,
	0x53, 0xf5, 0x04, 0x0c, 0x14, 0x3c, 0x44, 0xcc, 0x4f, 0xd1, 0x68, 0xb8, 0xd3, 0x6e, 0xb2, 0xcd,
	0x4c, 0xd4, 0x67, 0xa9, 0xe0, 0x3b, 0x4d, 0xd7, 0x62, 0xa6, 0xf1, 0x08, 0x18, 0x28, 0x78, 0x88,
	0x83, 0x9e, 0xb9, 0xd0, 0x6b, 0xbd, 0xdc, 0x7f, 0x81, 0x98, 0xb3, 0xce, 0x49, 0xdb, 0x76, 0x9a,
	0xb5, 0xc4, 0x57, 0xf9, 0x10, 0x30, 0x50, 0xf0, 0x0b, 0x1d, 0x27, 0x69, 0xbb, 0xd6, 0x61, 0xa3,
	0xfe, 0x19, 0x2b, 0x7d, 0x87, 0x92, 0xad, 0xec, 0x2f, 0x71, 0x93, 0xae, 0xe9, 0x20, 0x60, 0xa0,
	0xfb, 0x16, 0x3a, 0x4e, 0xd2, 0x6d, 0xb7, 0xc2, 0x5d, 0xe7, 0x32, 0x56, 0xfa, 0x15, 0x3f, 0x41,
	0xc3, 0x5e, 0xe2, 0x3d, 0x47, 0xc9, 0x40, 0xc0, 0x5b, 0xed, 0x2c, 0x74, 0x9c, 0xbf, 0xda, 0x75,
	0x9f, 0xba, 0xd5, 0x64, 0xac, 0xef, 0x2a, 0x7e, 0x82, 0x9d, 0xbc, 0xdf, 0x7a, 0x8e, 0x89, 0x80,
	0x9b, 0xb6, 0xc1, 0x58, 0xe8, 0x23, 0x65, 0xaf, 0xea, 0x25, 0x6f, 0xb1, 0xc8, 0x43, 0xc5, 0x54,
	0xfc, 0x1f, 0x21, 0x63, 0xa5, 0xf4, 0x07, 0x09, 0x1b, 0x2d, 0x77, 0x99, 0xb0, 0xcb, 0x46, 0xca,
	0x45, 0xcf, 0x4a, 0xde, 0x79, 0x8b, 0x86, 0x91, 0xa8, 0xe3, 0x3e, 0x42, 0xc6, 0x51, 0xf3, 0x0e,
	0x12, 0x36, 0x5a, 0xee, 0x29, 0x7b, 0x8d, 0x8c, 0x8f, 0x8a, 0x85, 0x94, 0xa7, 0xf2, 0x0d, 0x17,
	0x39, 0x4b, 0xdd, 0x7c, 0x84, 0x97, 0xa2, 0xfd, 0x1c, 0x24, 0x6c, 0xb4, 0xc7, 0x52, 0xf6, 0x01
};

unsigned char mix_columns_matrix[16] = {
	2, 3, 1, 1,
	1, 2, 3, 1,
	1, 1, 2, 3,
	3, 1, 1, 2
};

unsigned char s_box_table_index(unsigned char row, unsigned char col) {
	return s_box_table[row * 16 + col];
}

unsigned char table_L_index(unsigned char row, unsigned char col) {
	return table_L[row * 16 + col];
}

unsigned char *word(unsigned char *key, int index) {
	return &(key[index * 4]);
}

unsigned char *clone_word(unsigned char word[4]) {
	unsigned char *new_word = (unsigned char *) malloc(sizeof(unsigned char) * 4);
	new_word[0] = word[0];
	new_word[1] = word[1];
	new_word[2] = word[2];
	new_word[3] = word[3];
	return new_word;
}

unsigned char *rot_word_left(unsigned char *word) {
	unsigned char a_copy[4];
	a_copy[0] = word[0];
	a_copy[1] = word[1];
	a_copy[2] = word[2];
	a_copy[3] = word[3];
	word[0] = a_copy[1];
	word[1] = a_copy[2];
	word[2] = a_copy[3];
	word[3] = a_copy[0];
	return word;
}

unsigned char mapped_byte(unsigned char b) {
	unsigned char most_significant_nibble = (b & 0b11110000) >> 4;
	unsigned char least_significant_nibble = (b & 0b00001111);
	return s_box_table_index(most_significant_nibble, least_significant_nibble);
}

unsigned char mapped_byte_table_L(unsigned char b) {
	unsigned char most_significant_nibble = (b & 0b11110000) >> 4;
	unsigned char least_significant_nibble = (b & 0b00001111);
	return table_L_index(most_significant_nibble, least_significant_nibble);
}

unsigned char *map_word(unsigned char *word) {
	word[0] = mapped_byte(word[0]);
	word[1] = mapped_byte(word[1]);
	word[2] = mapped_byte(word[2]);
	word[3] = mapped_byte(word[3]);
	return word;
}

void map_matrix(unsigned char *matrix) {
	int i;
	for (i = 0; i < 16; i++) {
		matrix[i] = mapped_byte(matrix[i]);
	}
}

unsigned char *round_constant(int round_key_index) {
	unsigned char *word = (unsigned char *) malloc(sizeof(unsigned char) * 4);
	if (round_key_index < 8) {
		word[0] = 1 << round_key_index;
	} else if (round_key_index == 8) {
		word[0] = 0x1B;
	} else {
		word[0] = 0x36;
	}	
	word[1] = 0;
	word[2] = 0;
	word[3] = 0;
	return word;
}

void xor_words(unsigned char *w1, unsigned char *w2, unsigned char *to) {
	to[0] = w1[0] ^ w2[0];
	to[1] = w1[1] ^ w2[1];
	to[2] = w1[2] ^ w2[2];
	to[3] = w1[3] ^ w2[3];
}

void xor_keys(unsigned char *key1, unsigned char *key2, unsigned char *to) {
	xor_words(key1, key2, to);
	xor_words(&(key1[4]), &(key2[4]), &(to[4]));
	xor_words(&(key1[8]), &(key2[8]), &(to[8]));
	xor_words(&(key1[12]), &(key2[12]), &(to[12]));
}

void set_cur_round_key(struct round_key *prev_key, struct round_key *cur_key, int idx_cur_key) {
	unsigned char *last_word_prev_key = clone_word(prev_key -> word3);
	unsigned char *rotated_word = rot_word_left(last_word_prev_key);
	unsigned char *mapped_word = map_word(rotated_word);
	unsigned char *word_constant = round_constant(idx_cur_key - 1);

	xor_words(mapped_word, word_constant, (unsigned char *)&(cur_key -> word0));
	xor_words((unsigned char *)&(prev_key -> word0), (unsigned char *)&(cur_key -> word0), (unsigned char *)&(cur_key -> word0));
	xor_words((unsigned char *)&(prev_key -> word1), (unsigned char *)&(cur_key -> word0), (unsigned char *)&(cur_key -> word1));
	xor_words((unsigned char *)&(prev_key -> word2), (unsigned char *)&(cur_key -> word1), (unsigned char *)&(cur_key -> word2));
	xor_words((unsigned char *)&(prev_key -> word3), (unsigned char *)&(cur_key -> word2), (unsigned char *)&(cur_key -> word3));
}

void set_round_keys(struct round_key *original_key, struct round_key *round_keys) {
	round_keys[0] = *original_key;
	set_cur_round_key(&(round_keys[0]), &(round_keys[1]), 1);
	set_cur_round_key(&(round_keys[1]), &(round_keys[2]), 2);
	set_cur_round_key(&(round_keys[2]), &(round_keys[3]), 3);
	set_cur_round_key(&(round_keys[3]), &(round_keys[4]), 4);
	set_cur_round_key(&(round_keys[4]), &(round_keys[5]), 5);
	set_cur_round_key(&(round_keys[5]), &(round_keys[6]), 6);
	set_cur_round_key(&(round_keys[6]), &(round_keys[7]), 7);
	set_cur_round_key(&(round_keys[7]), &(round_keys[8]), 8);
	set_cur_round_key(&(round_keys[8]), &(round_keys[9]), 9);
	set_cur_round_key(&(round_keys[9]), &(round_keys[10]), 10);
}

void cpy_matrix(unsigned char *from, unsigned char *to) {
	int i;
	for (i = 0; i < 16; i++) {
		to[i] = from[i];
	}
}

void shift_matrix_rows(unsigned char *matrix) {
	unsigned char tmp = matrix[1];
	matrix[1] = matrix[5];
	matrix[5] = matrix[9];
	matrix[9] = matrix[13];
	matrix[13] = tmp;
	tmp = matrix[2];
	matrix[2] = matrix[10];
	matrix[10] = tmp;
	tmp = matrix[6];
	matrix[6] = matrix[14];
	matrix[14] = tmp;
	tmp = matrix[15];
	matrix[15] = matrix[11];
	matrix[11] = matrix[7];
	matrix[7] = matrix[3];
	matrix[3] = tmp;
}

void mix_columns_step(unsigned char *shift_rows_matrix, unsigned char *mix_columns_matrix) {
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++) {
				unsigned char r1 = mapped_byte_table_L();
				unsigned char multiplier = mapped_byte_table_L();
				unsigned char result;
				if (((unsigned int)r1 + (unsigned int)multitplier) > 255) {
					result = 255;
				} else {
					result = r1 + multiplier;
				}
				mix_columns_matrix[i * 4 + j] ^= result;
			}
		}
	}
//	mix_columns_matrix[0] = 
}

void set_matrix(unsigned char *matrix, unsigned char value) {
	int i;
	for (i = 0; i < 16; i++) {
		matrix[i] = value;
	}
}

int main() {
	struct round_key key = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
	unsigned char texto[16] = "DESENVOLVIMENTO!";
	struct round_key round_keys[11];
	set_round_keys(&key, &round_keys);

	//xor matrix
	unsigned char *xor_original_matrix_round_key_0 = (unsigned char *) malloc(sizeof(unsigned char) * 16);
	xor_keys((unsigned char *)&(round_keys[0]), texto, xor_original_matrix_round_key_0);
	print_key(xor_original_matrix_round_key_0);

	//sub_bytes matrix
	unsigned char *sub_bytes_matrix = (unsigned char *) malloc(sizeof(unsigned char) * 16);
	cpy_matrix(xor_original_matrix_round_key_0, sub_bytes_matrix);
	map_matrix(sub_bytes_matrix);
	print_key(sub_bytes_matrix);

	//shift_rows matrix
	unsigned char *shift_rows_matrix = (unsigned char *) malloc(sizeof(unsigned char) * 16);
	cpy_matrix(sub_bytes_matrix, shift_rows_matrix);
	shift_matrix_rows(shift_rows_matrix);
	print_key(shift_rows_matrix);

	//mix_columns matrix
	unsigned char *mix_columns_matrix = (unsigned char *) malloc(sizeof(unsigned char) * 16);
	set_matrix(mix_columns_matrix, 0);
	mix_columns_step(shift_rows_matrix, mix_columns_matrix);

}
