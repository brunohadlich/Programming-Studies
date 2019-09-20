//gcc -Wall -march=haswell -std=c11 -O2 -o a.out source_file.c
//clang -std=c11 -mavx avxvec.c -o avxvec
#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clear_array(float *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = 0;
}

void fill_from_to(float *array, int from, int to)
{
	for (int i = from; i < to; i++)
		array[i - from] = i;
}

void print_first_n(float * array, int n)
{
	for (int i = 0; i < n; i++)
		printf("%f ", array[i]);
	printf("\n");
}

void print_last_n(float * array, int size, int n)
{
	for (int i = size - 1; i > size - 1 - n; i--)
		printf("%f ", array[i]);
	printf("\n");
}

void benchmark_common_scalar_product(float * array, int size, float value)
{
	double t0 = clock();
    
    for (int i = 4; i < size; i++)
        array[i] *= value;
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_scalar_product_256_set(float * array, int size, float value)
{
	double t0 = clock();
	__m256 v2 = _mm256_set_ps(value, value, value, value, value, value, value, value);
    
    for (int i = 4; i <= size - 8; i+=8)
	{
        __m256 v = _mm256_set_ps(array[i+7], array[i+6], array[i+5], array[i+4], array[i+3], array[i+2], array[i+1], array[i]);
        __m256 sq = _mm256_mul_ps(v, v2);
        _mm256_store_ps(array + i, sq);
    }
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_scalar_product_256_load(float * array, int size, float value)
{
	double t0 = clock();
	__m256 v2 = _mm256_set1_ps(value);
    
    for (int i = 4; i <= size - 8; i+=8)
	{
        __m256 v = _mm256_load_ps(&array[i]);
        __m256 sq = _mm256_mul_ps(v, v2);
        _mm256_store_ps(array + i, sq);
    }
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_scalar_product_set_128(float * array, int size, float value)
{
	double t0 = clock();
	__m128 v2 = _mm_load_ps1(&value);
    
    for (int i = 4; i <= size - 4; i+=4)
	{
        __m128 v = _mm_set_ps(array[i+3], array[i+2], array[i+1], array[i]);
        __m128 sq = _mm_mul_ps(v, v2);
        _mm_store_ps(array + i, sq);
    }
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_scalar_product_load_128(float * array, int size, float value)
{
	double t0 = clock();
	__m128 v2 = _mm_load_ps1(&value);
    
    for (int i = 4; i <= size - 4; i+=4)
	{
        __m128 v = _mm_load_ps(&array[i]);
        __m128 sq = _mm_mul_ps(v, v2);
        _mm_store_ps(&array[i], sq);
    }
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_common_arrays_sum(float * array1, float * array2, int size)
{
	double t0 = clock();
    
    for (int i = 4; i < size; i++)
        array1[i] += array2[i];
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_arrays_sum_set_256(float * array1, float * array2, int size)
{
	double t0 = clock();
    
    for (int i = 4; i <= size - 8; i+=8)
	{
        __m256 v1 = _mm256_set_ps(array1[i+7], array1[i+6], array1[i+5], array1[i+4], array1[i+3], array1[i+2], array1[i+1], array1[i]);
		__m256 v2 = _mm256_set_ps(array2[i+7], array2[i+6], array2[i+5], array2[i+4], array2[i+3], array2[i+2], array2[i+1], array2[i]);
		
		__m256 result =_mm256_add_ps(v1, v2);
		
        _mm256_store_ps(array1 + i, result);
    }
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_arrays_sum_load_256(float * array1, float * array2, int size)
{
	double t0 = clock();
    
    for (int i = 4; i <= size - 8; i+=8)
	{
        __m256 v1 = _mm256_load_ps(&array1[i]);
		__m256 v2 = _mm256_load_ps(&array2[i]);
		
		__m256 result =_mm256_add_ps(v1, v2);
		
        _mm256_store_ps(array1 + i, result);
    }
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_common_arrays_fma(float * array1, float * array2, float * array3, int size)
{
	double t0 = clock();
    
    for (int i = 4; i < size; i++)
        array1[i] += array1[i] * array2[i] + array3[i];
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_arrays_fma_256(float * array1, float * array2, float * array3, int size)
{
	double t0 = clock();
    
    for (int i = 4; i <= size - 8; i+=8)
	{
        __m256 v1 = _mm256_load_ps(&array1[i]);
		__m256 v2 = _mm256_load_ps(&array2[i]);
		__m256 v3 = _mm256_load_ps(&array3[i]);
		
		__m256 result =_mm256_fmadd_ps(v1, v2, v3);
		
        _mm256_store_ps(array1 + i, result);
    }
    
    double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void benchmark_intrinsic_arrays_fma_128(float * array1, float * array2, float * array3, int size)
{
	double t0 = clock();
    
  for (int i = 4; i <= size - 4; i+=4)
	{
        __m128 v1 = _mm_load_ps(&array1[i]);
		__m128 v2 = _mm_load_ps(&array2[i]);
		__m128 v3 = _mm_load_ps(&array3[i]);
		
		__m128 result =_mm_fmadd_ps(v1, v2, v3);
		
        _mm_store_ps(array1 + i, result);
    }
    
  double t1 = clock();
	
	printf("%f\n", t1 - t0);
}

void matrices_product(float *matrix1, int rows1, int columns1, float *matrix2, int rows2, int columns2, float *matrix3)
{
  for (int row = 0; row < rows1; row++)
    for (int col = 0; col < columns2; col++)
      for (int i = 0; i < columns1; i++)
        matrix3[row*col] += matrix1[row*i] * matrix2[i*columns1];
}

void benchmark_matrices_product()
{
  const int size1 = 192, size2 = 108;
  float *m1 = malloc(sizeof(float) * size1 * size2);
  float *m2 = malloc(sizeof(float) * size2 * size1);
  float *m3 = malloc(sizeof(float) * size1 * size1);
  
  fill_from_to(m1, 0, size1 * size2);
  fill_from_to(m2, 0, size2 * size1);
  clear_array(m3, size1 * size1);
  
  double t0 = clock();
  
  matrices_product(m1, size1, size2, m2, size2, size1, m3);
  
  double t1 = clock();
  
  printf("%f\n", m3[53]);
  
  free(m1);
  free(m2);
  free(m3);
	
	printf("%f\n", t1 - t0);
}

//see https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX
int main()
{
	const int ARRAY_SIZE = 100000004;
	const int SCALAR_VALUE = 3;
	
  float *array = malloc(sizeof(float) * ARRAY_SIZE);
	
  printf("---------------------------------------------------------------------------\n");
	
	//conventional scalar product
	printf("common scalar product:\n");
  clear_array(array, ARRAY_SIZE);
	fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_common_scalar_product(array, ARRAY_SIZE, SCALAR_VALUE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
  //intrinsic scalar product 256
	printf("AVX2 scalar product set:\n");
  clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_scalar_product_256_set(array, ARRAY_SIZE, SCALAR_VALUE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
  //intrinsic scalar product 256
	printf("AVX2 scalar product load:\n");
  clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_scalar_product_256_load(array, ARRAY_SIZE, SCALAR_VALUE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
	//intrinsic scalar product 128 set
	printf("SSE scalar product set:\n");
	clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_scalar_product_set_128(array, ARRAY_SIZE, SCALAR_VALUE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
	//intrinsic scalar product 128 load
	printf("SSE scalar product load:\n");
	clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_scalar_product_load_128(array, ARRAY_SIZE, SCALAR_VALUE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
	//conventional sum
	printf("common sum:\n");
  clear_array(array, ARRAY_SIZE);
	fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_common_arrays_sum(array, array, ARRAY_SIZE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
  //intrinsic sum 256 set
  printf("AVX2 sum set:\n");
	clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_arrays_sum_set_256(array, array, ARRAY_SIZE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
	//intrinsic sum 256 load
  printf("AVX2 sum load:\n");
	clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_arrays_sum_load_256(array, array, ARRAY_SIZE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
  //common fma
  printf("common fma:\n");
	clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_common_arrays_fma(array, array, array, ARRAY_SIZE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
	//intrinsic fma
  printf("intrinsic fma 256:\n");
	clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_arrays_fma_256(array, array, array, ARRAY_SIZE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
	//intrinsic fma
  printf("intrinsic fma 128:\n");
	clear_array(array, ARRAY_SIZE);
  fill_from_to(array, 0, ARRAY_SIZE);
  benchmark_intrinsic_arrays_fma_128(array, array, array, ARRAY_SIZE);
	print_first_n(array, 10);
	print_last_n(array, ARRAY_SIZE, 10);
  
  free(array);
  
  //matrices product
  printf("common matrices product:\n");
  benchmark_matrices_product();
  printf("---------------------------------------------------------------------------\n");
    
	//printf("%f\n", array[5]);
	//__m256d v = _mm256_load_pd(array);
	//__m256d v = _mm256_set_pd(1, 2, 5, 4); // (e3, e2, e1, e1);
	//__m256d sq = _mm256_mul_pd(v, v);
	//__m256 v2 = _mm256_set_ps(1, 2, 3, 4, 5, 6, 7, 8); // (e3, e2, e1, e1);
	//_mm256_store_pd(array, sq);
	return 0;
}