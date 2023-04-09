#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "merge_sort.h"

// compare for array of integers
int compare_integers(int *v1, int *v2) {
    if (*v1 > *v2) {
        return 1;
    } else if (*v1 < *v2) {
        return -1;
    }
    return 0;
}

void test_integer_arrays() {
    int test1[10] = { 5, 3, 4, 9, 8, 6, 7, 1, 2, 10 };
    int test2[7] = { 5, 3, 4, 6, 7, 1, 2 };
    int test3[3] = { 1, 3, 2 };
    int test4[2] = { 2, 1 };
    int test5[1] = { 1 };

    int length;
    int *sorted;

    length = sizeof(test1) / sizeof(int);
    sorted = (int *)merge_sort((char *)test1, sizeof(int), length, (int (*)(void *, void *))compare_integers);
    for (int i = 0; i < length; i++) {
        printf("%d; ", sorted[i]);
    }
    printf("\n");

    length = sizeof(test2) / sizeof(int);
    sorted = (int *)merge_sort((char *)test2, sizeof(int), length, (int (*)(void *, void *))compare_integers);
    for (int i = 0; i < length; i++) {
        printf("%d; ", sorted[i]);
    }
    printf("\n");

    length = sizeof(test3) / sizeof(int);
    sorted = (int *)merge_sort((char *)test3, sizeof(int), length, (int (*)(void *, void *))compare_integers);
    for (int i = 0; i < length; i++) {
        printf("%d; ", sorted[i]);
    }
    printf("\n");

    length = sizeof(test4) / sizeof(int);
    sorted = (int *)merge_sort((char *)test4, sizeof(int), length, (int (*)(void *, void *))compare_integers);
    for (int i = 0; i < length; i++) {
        printf("%d; ", sorted[i]);
    }
    printf("\n");

    length = sizeof(test5) / sizeof(int);
    sorted = (int *)merge_sort((char *)test5, sizeof(int), length, (int (*)(void *, void *))compare_integers);
    for (int i = 0; i < length; i++) {
        printf("%d; ", sorted[i]);
    }
    printf("\n");
}

struct person {
    char *name;
    int age;
    char *sex;
};

// compare for array of struct person
int compare_struct_person(struct person *v1, struct person *v2) {
    if (v1 -> age > v2 -> age) {
        return 1;
    } else if (v1 -> age < v2 -> age) {
        return -1;
    }
    return 0;
}

void test_struct_person_array() {
    struct person people[] = {
        { name: "John Doe", age: 71, sex: "male" },
        { name: "Bob Boris", age: 36, sex: "male" },
        { name: "Jessie James", age: 43, sex: "female" },
        { name: "Cleveland Brown", age: 54, sex: "male" },
        { name: "John Boyer", age: 19, sex: "male" },
    };
    const int length = sizeof(people) / sizeof(struct person);
    struct person *sorted = (struct person *)merge_sort((char *)people, sizeof(struct person), length, (int (*)(void *, void *))compare_struct_person);
    for (int i = 0; i < length; i++) {
        printf("%d; ", sorted[i].age);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    test_integer_arrays();
    test_struct_person_array();

    return 0;
}
