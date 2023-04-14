#include <stdlib.h>
#include "heap.h"

struct heap *create_heap(int capacity) {
    if (capacity == 0) {
        return NULL;
    }
    struct heap *heap = (struct heap *)malloc(sizeof(struct heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (int *)malloc(sizeof(int) * capacity);
    return heap;
}

int get_parent_idx(int idx) {
    if (idx == 0) {
        return -1;
    }
    int parent = idx / 2;
    if (idx % 2 == 0) {
        return parent-1;
    }
    return parent;
}

void swap(struct heap *heap, int idx1, int idx2) {
    int tmp = heap->array[idx1];
    heap->array[idx1] = heap->array[idx2];
    heap->array[idx2] = tmp;
}

int insert(struct heap *heap, int el) {
    if (heap->size == heap->capacity) {
        return -1;
    }
    int curr_idx = heap->size;
    heap->array[curr_idx] = el;
    int parent_idx = get_parent_idx(curr_idx);
    while (parent_idx >= 0 && heap->array[curr_idx] > heap->array[parent_idx]) {
        swap(heap, curr_idx, parent_idx);
        curr_idx = parent_idx;
        parent_idx = get_parent_idx(curr_idx);
    }
    heap->size++;
    return 0;
}

void heapify(struct heap *heap, int idx) {
    int max_idx = idx;
    int max_value = heap->array[max_idx];
    if (2*idx + 1 < heap->size && heap->array[2*idx + 1] > heap->array[max_idx]) {
        max_idx = 2*idx + 1;
    }
    if (2*idx + 2 < heap->size && heap->array[2*idx + 2] > heap->array[max_idx]) {
        max_idx = 2*idx + 2;
    }
    if (idx != max_idx) {
        swap(heap, idx, max_idx);
        heapify(heap, max_idx);
    }
}

int delete_idx(struct heap *heap, int idx) {
    if (heap->size == 0) {
        return -1;
    }
    heap->array[idx] = heap->array[heap->size-1];
    heapify(heap, idx);
    heap->size--;
    return 0;
}

int peek(struct heap *heap) {
    if (heap->size == 0) {
        return -1;
    }
    return heap->array[0];
}

int pop(struct heap *heap) {
    int value = peek(heap);
    delete_idx(heap, 0);
    return value;
}