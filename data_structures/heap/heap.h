#ifndef HEAP_H
#define HEAP_H

struct heap {
    int size;
    int capacity;
    int *array;
};

struct heap *create_heap(int capacity);
int insert(struct heap *heap, int el);
int peek(struct heap *heap);
int pop(struct heap *heap);

#endif