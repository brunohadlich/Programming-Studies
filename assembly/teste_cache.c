#include <stdlib.h>
#include <stdio.h>
#include <time.h>

__uint8_t *get_byte_array(__int32_t size)
{
    return (__uint8_t *)malloc(size);
}

__int32_t *get_int32_array(__int32_t size)
{
    return (__int32_t *)malloc(size * sizeof(__int32_t));
}

void fill_byte_array_random(__uint8_t *arr, __int32_t size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = (__uint8_t)rand();
    }
}

void fill_int32_array_random(__int32_t *arr, __int32_t size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        arr[i] = (__int32_t)rand();
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

void copy_int32_array(__int32_t *arr_from, __int32_t *arr_to, __int32_t size) {
    for (__int32_t i = 0; i < size; i++) {
        arr_to[i] = arr_from[i];
    }
}

void fill_array_sequence(__int32_t *arr, __int32_t size) {
    __int32_t i;
    for (i = 0; i < size; i++) {
        arr[i] = i;
    }
}

void fisher_yates_shuffle(__int32_t *arr, __int32_t size) {
    __int32_t i, idx;
    __int32_t pivot;
    //srand(time(NULL));
    for (i = 0; i < size; i++) {
        pivot = arr[i];
        idx = rand() % (size - i);
        arr[i] = arr[i + idx];
        arr[i + idx] = pivot;
    }
}

void shuffle(__int32_t *arr, __int32_t size) {
    fisher_yates_shuffle(arr, size);
}

__int64_t sum(__int32_t *arr, __int32_t size) {
    __int32_t i;
    __int64_t total;
    for (total = 0, i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

void count_not_filled(__uint8_t *arr, __int32_t size) {
    __uint8_t *flags = get_byte_array(size);
    __int32_t i, counter = 0;
    
    for (i = 0; i < size; i++) {
        flags[i] = 0;
    }
    for (i = 0; i < size; i++) {
        flags[arr[i]] = 1;
    }
    for (i = 0; i < size; i++) {
        if (flags[i] == 0) {
            counter++;
        }
    }
    free(flags);
    printf("Não tem %d elementos.\n", counter);
}

void test_randomized_vs_sequential_access()
{
    const __int32_t SIZE = 64*1024*1024;
    __int32_t *values = get_int32_array(SIZE);
    __int32_t *randomized = get_int32_array(SIZE);
    fill_array_sequence(values, SIZE);
    copy_int32_array(values, randomized, SIZE);
    shuffle(randomized, SIZE);
    clock_t t0, t1;
    __int32_t i;
    __int64_t total;
    //printf("sum of values: %lu\n", sparse_sum(values, SIZE, 64));
    //printf("sum of randomized: %lu\n", sparse_sum(randomized, SIZE, 64));
    
    t0 = clock();
    for (total = 0, i = 0; i < SIZE; i++) {
        total += values[values[i]];
    }
    t1 = clock();
    printf("Access with sequential index, total %li. time: %li.\n", total, t1 - t0);
    
    t0 = clock();
    for (total = 0, i = 0; i < SIZE; i++) {
        total += randomized[values[i]];
    }
    t1 = clock();
    printf("Access with sequential index, total %li. time: %li.\n", total, t1 - t0);
    
    t0 = clock();
    for (total = 0, i = 0; i < SIZE; i++) {
        total += values[randomized[i]];
    }
    t1 = clock();
    printf("Access with random index, total %li. time: %li.\n", total, t1 - t0);
    
    t0 = clock();
    for (total = 0, i = 0; i < SIZE; i++) {
        total += randomized[randomized[i]];
    }
    t1 = clock();
    printf("Access with random index, total %li. time: %li.\n", total, t1 - t0);

    //test_long_sum_extrapolating_line_cache();
    //cache_speed_test();
}

int main()
{
    const __int32_t L1_CACHE_SIZE = 64 * 1024 / sizeof(__int32_t);
    const __int32_t L2_CACHE_SIZE = 512 * 1024 / sizeof(__int32_t);
    const __int32_t L3_CACHE_SIZE = 3 * 1024 * 1024 / sizeof(__int32_t);
    const __int32_t SIZE = L1_CACHE_SIZE + L2_CACHE_SIZE + L3_CACHE_SIZE;
    __int32_t *arr = get_int32_array(SIZE);
    fill_int32_array_random(arr, SIZE);
    clock_t t0, t1;
    __int64_t total;
    __int32_t i, x;
    __int64_t time_L1, time_L2, time_L3;
    /*
    for (x = 0; x < 50; x++) {
        t0 = clock();
        for (total = 0, i = 0; i < L1_CACHE_SIZE; i++) {
            total += arr[i];
        }
        t1 = clock();
        time_L1 = t1 - t0;
        printf("total: %li; %li\n", total, time_L1);
    }
    */
    printf("===================\n");
    /*
    for (x = 0; x < 50; x++) {
        t0 = clock();
        for (total = 0, i = 0; i < L2_CACHE_SIZE + L1_CACHE_SIZE; i++) {
            total += arr[i];
        }
        t1 = clock();
        time_L2 = t1 - t0;
        printf("total: %li; %li\n", total, (time_L2) / ((L1_CACHE_SIZE + L2_CACHE_SIZE) / L1_CACHE_SIZE));
    }
    printf("===================\n");
    for (x = 0; x < 50; x++) {
        t0 = clock();
        for (total = 0, i = 0; i < L3_CACHE_SIZE + L2_CACHE_SIZE + L1_CACHE_SIZE; i++) {
            total += arr[i];
        }
        t1 = clock();
        time_L3 = t1 - t0;
        printf("total: %li; %li\n", total, (time_L3) / ((L3_CACHE_SIZE + L2_CACHE_SIZE + L1_CACHE_SIZE) / L1_CACHE_SIZE));
    }
    */
    free(arr);
    //test_randomized_vs_sequential_access()
    //test_long_sum_extrapolating_line_cache();
    //cache_speed_test();
}