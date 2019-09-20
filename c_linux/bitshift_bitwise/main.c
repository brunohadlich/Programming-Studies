#include <stdio.h>
#include <math.h>
#include <inttypes.h>

void print_bits(uint32_t value) {
	int i;

	printf("%u: ", value);
	for (i = 31; i >= 0; i--) {
		printf("%u", ((((uint32_t)pow(2, (double)i))&value)>>i));
	}
	printf("\n");
}

int main() {
	print_bits(1);//001
	print_bits(2);//010
	print_bits(4);//100
	print_bits(5);//101
	print_bits(6);//110
	print_bits(7);//111
	//bitwise complement, flip the bits
	print_bits(~1);// ~1 = 1111111111110
	print_bits(~7);// ~7 = 1111111111000
	//bitwise and
	print_bits(7 & 1);//=1; 111 & 001 = 001
	print_bits(7 & 2);//=2; 111 & 010 = 010
	print_bits(7 & 4);//=4; 111 & 100 = 100
	print_bits(7 & 5);//=5; 111 & 101 = 101
	print_bits(7 & 6);//=6; 111 & 110 = 110
	print_bits(7 & 7);//=7; 111 & 111 = 000
	print_bits(4 & 7);//=4; 100 & 111 = 100
	//bitwise or
	print_bits(7 | 8);//=15; 111 | 1000 = 1111
	print_bits(7 | 16);//=23; 111 | 10000 = 10111
	print_bits(7 | 8 | 16);//=31; 111 | 1000 | 10000 = 11111
	//bitwise xor
	print_bits(7 ^ 1);//=6; 111 ^ 001 = 6
	print_bits(7 ^ 2);//=5; 111 ^ 010 = 5
	print_bits(7 ^ 4);//=3; 111 ^ 100 = 3
	print_bits(7 ^ 5);//=2; 111 ^ 101 = 2
	print_bits(7 ^ 6);//=1; 111 ^ 110 = 1
	print_bits(7 ^ 7);//=0; 111 ^ 111 = 0
	//bit shift left
	print_bits(7 << 1);//=14; 111 << 1 = 1110
	print_bits(7 << 2);//=28; 111 << 2 = 11100
	//bit shift right
	print_bits(7 >> 1);//=3; 111 >> 1 = 011
	print_bits(7 >> 2);//=1; 111 >> 2 = 001
	//bit rotate left
	print_bits((7 << 1)|(7 >> (32 - 1)));//111 <<< 1 = 00000000000000000000000000001110
	print_bits((7 << 2)|(7 >> (32 - 2)));//111 <<< 2 = 00000000000000000000000000011100
	//bit rotate right
	print_bits((7 >> 1)|(7 << (32 - 1)));//111 >>> 1 = 10000000000000000000000000000011
	print_bits((7 >> 2)|(7 << (32 - 2)));//111 >>> 2 = 11000000000000000000000000000001
}
