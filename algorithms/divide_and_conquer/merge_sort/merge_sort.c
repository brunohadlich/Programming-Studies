#include <stdlib.h>
#include <string.h>

char *_merge_sort(char *array, int el_size, int length, int (*comparator)(void *, void *), char *result) {
    if (length > 1) {
        const int middle = length / 2;
        const int arr1_length = middle;
        const int arr2_length = middle + (length % 2);
        char *arr1 = _merge_sort(array, el_size, arr1_length, comparator, result);
        char *arr2 = _merge_sort(&array[el_size * arr1_length], el_size, arr2_length, comparator, result);
        for (int i = 0, x = 0, y = 0; i < length; i++) {
            if (x < arr1_length && y < arr2_length) {
                int direction = comparator(&arr1[x * el_size], &arr2[y * el_size]);
                if (direction < 0) {
                    memcpy(&result[i * el_size], &arr1[x * el_size], el_size);
                    x++;
                } else if (direction > 0) {
                    memcpy(&result[i * el_size], &arr2[y * el_size], el_size);
                    y++;
                }
            } else if (x < arr1_length) {
                memcpy(&result[i * el_size], &arr1[x * el_size], el_size);
                x++;
            } else if (y < arr2_length) {
                memcpy(&result[i * el_size], &arr2[y * el_size], el_size);
                y++;
            }
        }
        for (int i = 0; i < length * el_size; i++) {
            array[i] = result[i];
        }
    }
    return array;
}

char *merge_sort(char *array, int el_size, int length, int (*comparator)(void *, void *)) {
    char *result = (char *)malloc(el_size * length);
    return _merge_sort(array, el_size, length, comparator, result);
}
