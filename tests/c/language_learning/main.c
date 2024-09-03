#include <stdio.h>
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

	struct bit_fields {
		unsigned char field_1: 3;
		unsigned char field_2: 2;
		unsigned char field_3: 2;
	} bit_fields_variable;

	printf("Size of bit_fields_variable: %d\n", sizeof(bit_fields_variable));

	bit_fields_variable.field_3 = 2;

	printf("%d\n", bit_fields_variable);

	typedef struct {
		int a;
	} fooo;

	fooo x;

	x.a = 3;

	printf("%d\n", x.a);

	return 0;
}
