#include <stdlib.h>
#include <stdio.h>
#include <time.h>

__uint8_t *get_byte_array(__int32_t size)
{
    return (__uint8_t *)malloc(size);
}

void fill_byte_array_random(__uint8_t *arr, __int32_t size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = (__uint8_t)rand();
    }
}

__uint64_t sparse_sum(__uint8_t *arr, __int32_t size, __int32_t multiple)
{
    __int32_t i, k;
    __uint64_t total = 0;
    for (i = 0; i < multiple; i++)
    {
        for (k = 0; k < size; k += multiple)
        {
            total += arr[k + i];
        }
    }
    return total;
}

__uint64_t fastest_single_core_byte_array_sum(__uint8_t *arr, __int32_t size)
{
    __int32_t i;
    __uint64_t total = 0;
    for (i = 0; i < size; i += 8)
    {
        total += arr[i] + arr[i + 1] + arr[i + 2] + arr[i + 3] + arr[i + 4] + arr[i + 5] + arr[i + 6] + arr[i + 7];
    }
    return total;
}

void test_long_sum_extrapolating_line_cache() {
    __int32_t SIZE = 512 * 1024 * 1024;
    __uint8_t *values = get_byte_array(SIZE);

    fill_byte_array_random(values, SIZE);

    clock_t start, end;

    __int32_t i;
    for (i = 1; i <= 256; i *= 2)
    {
        start = clock();
        __uint64_t sum = sparse_sum(values, SIZE, i);
        end = clock();
        printf("multiple: %d\n", i);
        printf("sum: %lu\n", sum);
        printf("time: %li\n", end - start);
        printf("=========\n");
    }

    free(values);
}

void cache_l_speed_test(__uint8_t *values, __int32_t arr_size, __int32_t cache_size, __int32_t l)
{
    __int32_t i;
    __uint64_t sum = 0;
    clock_t start = clock();
    for (i = 0; i <= arr_size/cache_size; i++)
    {
        sum += sparse_sum(values, cache_size, 64);
    }
    clock_t end = clock();
    printf("Number of iterations: %d\n", arr_size);
    printf("Cache l%d\n", l);
    printf("multiple: %d\n", 64);
    printf("sum: %lu\n", sum);
    printf("time: %li\n", end - start);
    printf("=========\n");
}

void cache_speed_test() {
    __int32_t SIZE = 3 * 1024 * 1024;
    __uint8_t *values = get_byte_array(SIZE);
    fill_byte_array_random(values, SIZE);

    cache_l_speed_test(values, SIZE, 64 * 1024, 1);
    cache_l_speed_test(values, SIZE, 512 * 1024, 2);
    cache_l_speed_test(values, SIZE, 3 * 1024 * 1024, 3);

    free(values);
}

void copy_byte_array(__uint8_t *arr_from, __uint8_t *arr_to, __int32_t size) {
    for (__int32_t i = 0; i < size; i++) {
        arr_to[i] = arr_from[i];
    }
}

void fill_array_sequence(__uint8_t *arr, __int32_t size) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = i;
    }
}

void fisher_yates_shuffle(__uint8_t *arr, __int32_t size) {
    __int32_t i, idx;
    __uint8_t pivot;
    for (i = 0; i < size; i++) {
        pivot = arr[i];
        idx = rand() % (size - i);
        arr[i] = arr[i + idx];
        arr[i + idx] = pivot;
    }
}

void shuffle(__uint8_t *arr, __int32_t size) {
    fisher_yates_shuffle(arr, size);
}

int main()
{
    const __uint32_t SIZE = 256*1024*1024;
    __uint8_t *values = get_byte_array(SIZE);
    __uint8_t *randomized = get_byte_array(SIZE);
    fill_array_sequence(values, SIZE);
    copy_byte_array(values, randomized, SIZE);
    shuffle(randomized, SIZE);
    printf("%lu", sparse_sum(values, SIZE, 64));
    printf("%lu", sparse_sum(randomized, SIZE, 64));
    //test_long_sum_extrapolating_line_cache();
    //cache_speed_test();
}