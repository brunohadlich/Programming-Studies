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

int main(int argc, char* argv[]) {
	printf("%ld\n", sizeof(4));
	printf("%ld\n", sizeof(4u));
	printf("%ld\n", sizeof(4l));
	printf("%ld\n", sizeof(4L));
	printf("%ld\n", sizeof(4uL));
	printf("%ld\n", sizeof(4UL));
	printf("%ld\n", sizeof(4Lu));
	printf("%ld\n", sizeof(4LU));

	printf("%ld\n", sizeof(4e2));
	printf("%ld\n", sizeof(4e2f));
	printf("%ld\n", sizeof(4e2F));
	printf("%ld\n", sizeof(4e2l));
	printf("%ld\n", sizeof(4e2L));

	printf("%d\n", 6 % 4);
	char char_v = 150;
	printf("%d\n", char_v);

	short short_v1 = 123;
	short int short_v2 = 123;
	signed short int short_v3 = 123;
	unsigned short int short_v4 = 123;
	short short_v5 = 123;
	signed short short_v6 = 123;
	unsigned short short_v7 = 123;
	printf("Size of char %ld\n", sizeof(char));
	printf("Size of short %ld\n", sizeof(short));
	printf("Size of int %ld\n", sizeof(int));
	printf("Size of long %ld\n", sizeof(long));
	printf("Size of long long %ld\n", sizeof(long long));
	printf("Size of float %ld\n", sizeof(float));
	printf("Size of double %ld\n", sizeof(double));

	enum enum_test {abc, def, ghi};
	enum enum_test_2 {abcd};
			printf("%d\n", abc);
			printf("%d\n", def);
			printf("%d\n", ghi);
			printf("%d\n", abcd);
	enum enum_test foo = abc;
	switch (foo) {
		case abc:
			printf("abc\n");
			break;
		case def:
			printf("def\n");
			break;
		case ghi:
			printf("ghi\n");
			break;
	}

	// struct with 7 bits but compiler rounds to 8 bits (1 byte)
	struct bit_fields {
		unsigned char field_1: 3; // 3 bits
		unsigned char field_2: 2; // 2 bits
		unsigned char field_3: 2; // 2 bits
	} bit_fields_variable;

	printf("Size of bit_fields_variable: %ld\n", sizeof(bit_fields_variable));

	// 7 is the limit because field_1 has 3 bits of size
	bit_fields_variable.field_1 = (unsigned char)7;
	// 3 is the limit because field_2 has 2 bits of size
	bit_fields_variable.field_2 = (unsigned char)2;
	// 3 is the limit because field_3 has 2 bits of size
	bit_fields_variable.field_3 = (unsigned char)3;

	printf("%u\n", (unsigned char)bit_fields_variable.field_1); // 7
	printf("%u\n", (unsigned char)bit_fields_variable.field_2); // 2
	printf("%u\n", (unsigned char)bit_fields_variable.field_3); // 3

	typedef struct {
		int a;
	} fooo;

	fooo x;

	x.a = 3;

	printf("%d\n", x.a);

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

	return 0;
}
