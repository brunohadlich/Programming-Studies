#include "my_intrinsics.h"
#include <immintrin.h>

void add_floats_intrinsics_128(float *p_f1_vector, float *p_f2_vector, float *result, int size) {
	__m128 f1_vector, f2_vector;
	int i, until;
	until = size/4;
	for (i = 0; i < until - 4; i+=4) {
		f1_vector = _mm_load_ps(&p_f1_vector[i]);
		f2_vector = _mm_load_ps(&p_f2_vector[i]);

		__m128 result2 = _mm_add_ps(f1_vector, f2_vector);

		_mm_store_ps(&result[i], result2);
	}

	for (; i < until; i++) {
		result[i] = p_f1_vector[i] + p_f2_vector[i];
	}
}

void add_floats_intrinsics_256(float *p_f1_vector, float *p_f2_vector, float *result, int size) {
	__m256 f1_vector, f2_vector;
	int i, until;
	until = size/8;
	for (i = 0; i < until - 8; i+=8) {
		f1_vector = _mm256_loadu_ps(&p_f1_vector[i]);
		f2_vector = _mm256_loadu_ps(&p_f2_vector[i]);

		__m256 result2 = _mm256_add_ps(f1_vector, f2_vector);

		_mm256_storeu_ps(&result[i], result2);
	}

	for (; i < until; i++) {
		result[i] = p_f1_vector[i] + p_f2_vector[i];
	}
}
