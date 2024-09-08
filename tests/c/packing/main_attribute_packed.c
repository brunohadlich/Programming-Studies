#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct s1 {
	long double v1;
	char v2;
	long double v3;
	char v4;
	long double v5;
	char v6;
	long double v7;
} __attribute__((packed));

//static_assert(sizeof(struct s1) == 128, "sizeof(struct s1) should be 128 bytes.");

struct s2 {
	long double v1;
	long double v3;
	long double v5;
	long double v7;
	char v2;
	char v4;
	char v6;
} __attribute__((packed));

const int ARRAY_SIZE = 1000000;

void test_struct_s1() {
	printf("Size struct s1: %lu bytes.\n", sizeof(struct s1));
	struct s1 *array = (struct s1*)malloc(sizeof(struct s1) * ARRAY_SIZE);
	if (array == NULL) {
		printf("malloc failed.");
	}
	int i;
	clock_t t0 = clock();
	for (i = 0; i < ARRAY_SIZE; i++) {
		array[i].v2 = 'A';
	}
	clock_t t1 = clock();
	printf("Iterating over %d struct s1 elements took %lu clocks.\n", ARRAY_SIZE, t1 - t0);
}

void test_struct_s2() {
	printf("Size struct s2: %lu bytes.\n", sizeof(struct s2));
	struct s2 *array = (struct s2*)malloc(sizeof(struct s2) * ARRAY_SIZE);
	if (array == NULL) {
		printf("malloc failed.");
	}
	int i;
	clock_t t0 = clock();
	for (i = 0; i < ARRAY_SIZE; i++) {
		array[i].v2 = 'A';
	}
	clock_t t1 = clock();
	printf("Iterating over %d struct s2 elements took %lu clocks.\n", ARRAY_SIZE, t1 - t0);
}

int main() {
	printf("long double: %lu\n", sizeof(long double));
	test_struct_s1();
	test_struct_s2();
}
