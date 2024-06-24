#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <x86intrin.h>

const size_t KILO = 1024;
const size_t MEGA = 1024 * KILO;
const size_t GIGA = 1024 * MEGA;
const size_t sizes[] = {
    // 1 * KILO,
    // 10 * KILO,
    // 100 * KILO,
    // 1 * MEGA,
    // 10 * MEGA,
    // 100 * MEGA,
    1 * GIGA,
    2 * GIGA,
    4 * GIGA,
    8 * GIGA};

char *allocate_memory(size_t sz)
{
    char *block = (char *)malloc(sz + 64);
    if (block == NULL)
    {
        printf("error");
        exit(1);
    }
    return block;
}

void test_copy_with_memcpy(size_t sz)
{
    char *block_1 = allocate_memory(sz);
    char *block_2 = allocate_memory(sz);
    clock_t t0 = clock();
    memcpy(block_2, block_1, sz);
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using memcpy.\n", t1 - t0, sz);
    free(block_1);
    free(block_2);
}

void test_copy_with_1_byte_for_loop(size_t sz)
{
    char *block_1 = allocate_memory(sz);
    char *block_2 = allocate_memory(sz);
    clock_t t0 = clock();
    for (unsigned long int i = 0; i < sz; i++)
    {
        block_2[i] = block_1[i];
    }
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using for loop with 1 byte at a time.\n", t1 - t0, sz);
    free(block_1);
    free(block_2);
}

void test_copy_with_2_bytes_for_loop(size_t sz)
{
    char *block_1 = allocate_memory(sz);
    char *block_2 = allocate_memory(sz);
    clock_t t0 = clock();
    for (unsigned long int i = 0; i < sz / 2; i++)
    {
        ((short *)block_2)[i] = ((short *)block_1)[i];
    }
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using for loop with 2 bytes at a time.\n", t1 - t0, sz);
    free(block_1);
    free(block_2);
}

void test_copy_with_4_bytes_for_loop(size_t sz)
{
    char *block_1 = allocate_memory(sz);
    char *block_2 = allocate_memory(sz);
    clock_t t0 = clock();
    for (unsigned long int i = 0; i < sz / 4; i++)
    {
        ((int *)block_2)[i] = ((int *)block_1)[i];
    }
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using for loop with 4 bytes at a time.\n", t1 - t0, sz);
    free(block_1);
    free(block_2);
}

void test_copy_with_8_bytes_for_loop(size_t sz)
{
    char *block_1 = allocate_memory(sz);
    char *block_2 = allocate_memory(sz);
    clock_t t0 = clock();
    for (unsigned long int i = 0; i < sz / 8; i++)
    {
        ((long int *)block_2)[i] = ((long int *)block_1)[i];
    }
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using for loop with 8 bytes at a time.\n", t1 - t0, sz);
    free(block_1);
    free(block_2);
}

void test_copy_with_16_bytes_for_loop(size_t sz)
{
    char *block_1 = allocate_memory(sz);
    char *block_2 = allocate_memory(sz);
    clock_t t0 = clock();
    for (unsigned long int i = 0; i < sz; i += 16)
    {
        __m128i data = _mm_load_si128((__m128i *)(block_1 + i));
        _mm_store_si128((__m128i *)(block_2 + i), data);
    }
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using for loop with 16 bytes at a time.\n", t1 - t0, sz);
    free(block_1);
    free(block_2);
}

void test_copy_with_32_bytes_for_loop(size_t sz)
{
    char *original_block_1 = allocate_memory(sz);
    char *block_1 = original_block_1;
    while ((long int)block_1 % 32 > 0)
    {
        block_1++;
    }
    char *original_block_2 = allocate_memory(sz);
    char *block_2 = original_block_2;
    while ((long int)block_2 % 32 > 0)
    {
        block_2++;
    }
    clock_t t0 = clock();
    for (unsigned long int i = 0; i < sz; i += 32)
    {
        __m256i data = _mm256_load_si256((__m256i *)(block_1 + i));
        _mm256_store_si256((__m256i *)(block_2 + i), data);
    }
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using for loop with 32 bytes at a time.\n", t1 - t0, sz);
    free(original_block_1);
    free(original_block_2);
}

void test_copy_with_64_bytes_for_loop(size_t sz)
{
    char *original_block_1 = allocate_memory(sz);
    char *block_1 = original_block_1;
    while ((long int)block_1 % 64 > 0)
    {
        block_1++;
    }
    char *original_block_2 = allocate_memory(sz);
    char *block_2 = original_block_2;
    while ((long int)block_2 % 64 > 0)
    {
        block_2++;
    }
    clock_t t0 = clock();
    for (unsigned long int i = 0; i < sz; i += 64)
    {
        __m512i data = _mm512_load_si512((__m512i *)(block_1 + i));
        _mm512_store_si512((__m512i *)(block_2 + i), data);
    }
    clock_t t1 = clock();
    printf("It took %ld clocks to transfer %ld bytes using for loop with 64 bytes at a time.\n", t1 - t0, sz);
    free(original_block_1);
    free(original_block_2);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < sizeof(sizes) / sizeof(size_t); i++)
    {
        printf("====================================\n");
        printf("test_copy_with_memcpy:\n");
        test_copy_with_memcpy(sizes[i]);
        printf("test_copy_with_1_byte_for_loop:\n");
        test_copy_with_1_byte_for_loop(sizes[i]);
        printf("test_copy_with_2_bytes_for_loop:\n");
        test_copy_with_2_bytes_for_loop(sizes[i]);
        printf("test_copy_with_4_bytes_for_loop:\n");
        test_copy_with_4_bytes_for_loop(sizes[i]);
        printf("test_copy_with_8_bytes_for_loop:\n");
        test_copy_with_8_bytes_for_loop(sizes[i]);
        printf("test_copy_with_16_bytes_for_loop:\n");
        test_copy_with_16_bytes_for_loop(sizes[i]);
        printf("test_copy_with_32_bytes_for_loop:\n");
        test_copy_with_32_bytes_for_loop(sizes[i]);
        printf("test_copy_with_64_bytes_for_loop:\n");
        test_copy_with_64_bytes_for_loop(sizes[i]);
        printf("====================================\n");
    }
    return 0;
}