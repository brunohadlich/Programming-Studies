/*
 * =====================================================================================
 *
 *       Filename:  parallel_merge_sort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/19/2019 08:37:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include "merge_sort.h"
#include "utils.h"

struct merge_args {
	int *array, p, q, r;
};

void *merge(void *struct_merge_args) {
	int *array = ((struct merge_args *)struct_merge_args) -> array;
	int p = ((struct merge_args *)struct_merge_args) -> p;
	int q = ((struct merge_args *)struct_merge_args) -> q;
	int r = ((struct merge_args *)struct_merge_args) -> r;
	int *aux_array = (int *)malloc(sizeof(int) * (r - p + 1));
	int i, j, k;
	for (i = p, j = q + 1, k = 0; i <= q && j <= r; k++) {
		if (array[i] < array[j]) {
			aux_array[k] = array[i];
			i++;
		} else {
			aux_array[k] = array[j];
			j++;
		}
	}
	for (; i <= q; i++) {
		aux_array[k] = array[i];
		k++;
	}
	for (; j <= r; j++) {
		aux_array[k] = array[j];
		k++;
	}
	for (i = 0; i < (r - p + 1); i++) {
		array[p + i] = aux_array[i];
	}
	free(aux_array);
	return NULL;
}

struct merge_sort_args {
	int *array, p, r;
};

void *single_thread_merge_sort(void *args) {
	struct merge_sort_args *p = (struct merge_sort_args *)args;
	struct merge_args m;
	int middle;
	if (p -> p < p -> r) {
		middle = ((p -> p + p -> r) / 2);
		struct merge_sort_args s1 = {p -> array, p -> p, middle};
		struct merge_sort_args s2 = {p -> array, middle + 1, p -> r};
		single_thread_merge_sort((void *)&s1);
		single_thread_merge_sort((void *)&s2);
		m.array = p -> array;
		m.p = p -> p;
		m.q = middle;
		m.r = p -> r;
		merge((void *)&m);
	}
	return NULL;
}

void multi_thread_merge_sort(int *array, int p, int r, int threads) {
	pthread_t *thread_ids = (pthread_t *) malloc(sizeof(pthread_t) * threads);
	struct merge_sort_args *thread_args = (struct merge_sort_args *) malloc(sizeof(struct merge_sort_args) * threads);
	int i, j;
	int div = (r + 1) / threads;
	for (i = 0; i < threads; i++) {
		thread_args[i].array = array;
		thread_args[i].p = i * div;
		if (i != 0) {
			thread_args[i].p += 1;
		}
		if (i == threads - 1) {
			thread_args[i].r = r;
		} else {
			thread_args[i].r = (i + 1) * div;
		}

		pthread_create(&thread_ids[i], NULL, single_thread_merge_sort, (void *)&thread_args[i]);
	}

	for (i = 0; i < threads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	if (threads == 1) {
		return;
	}

	free(thread_ids);

	for (i = threads/2; i >= 1; i/=2) {
		pthread_t *thread_ids = (pthread_t *) malloc(sizeof(pthread_t) * i);
		struct merge_args *m = (struct merge_args *)malloc(sizeof(struct merge_args) * i);
		for (j = 0; j < i; j++) {
			m[j].array = array;
			m[j].p = thread_args[j * (threads / i)].p;
			m[j].q = thread_args[(j * (threads / i)) + ((((j + 1) * (threads / i) - 1) - (j * (threads / i))) / 2)].r;
			m[j].r = thread_args[(j + 1) * (threads / i) - 1].r;
			pthread_create(&thread_ids[j], NULL, merge, (void *)&m[j]);
		}
		for (j = 0; j < i; j++) {
			pthread_join(thread_ids[j], NULL);
		}
		free(m);
		free(thread_ids);
	}
	free(thread_args);
}

void merge_sort(int *array, int length) {
	int threads = 1;
	if (length >= 1000) {
		threads = get_nprocs();
		if (threads != 512 && threads != 256 && threads != 128 &&
		    threads != 64 && threads != 32 && threads != 16 &&
		    threads != 8 && threads != 4 && threads != 2 &&
		    threads != 1) {
			if (threads < 4) {
				threads = 4;
			} else if (threads < 8) {
				threads = 8;
			} else if (threads < 16) {
				threads = 16;
			} else if (threads < 32) {
				threads = 32;
			} else if (threads < 64) {
				threads = 64;
			} else if (threads < 128) {
				threads = 128;
			} else if (threads < 256) {
				threads = 256;
			} else if (threads < 512) {
				threads = 512;
			}
		}
	}
	multi_thread_merge_sort(array, 0, length - 1, threads);
}
