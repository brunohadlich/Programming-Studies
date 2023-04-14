#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

int main(int argc, char *argv[]) {
    struct heap *heap = create_heap(9);
    insert(heap, 5);
    insert(heap, 3);
    insert(heap, 6);
    insert(heap, 8);
    insert(heap, 2);
    insert(heap, 1);
    insert(heap, 9);
    insert(heap, 4);
    insert(heap, 7);
    while (heap->size > 0) {
        printf("%d\n", pop(heap));
    }
    return EXIT_SUCCESS;
}