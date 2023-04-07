#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    printf("Give the length of the array: ");
    int length;
    scanf("%d", &length);
    int *values = (int *)malloc(sizeof(int) * length);
    // generate random numbers
    srand(time(0));
    printf("Unsorted values: ");
    for (int i = 0; i < length; i++) {
        values[i] = rand() % length;
        printf("%d; ", values[i]);
    }
    // sort those numbers
    for (int i = 0; i < length; i++) {
        int lowest_idx = i;
        int y = values[lowest_idx];
        for (y = i; y < length; y++) {
            if (values[y] < values[lowest_idx]) {
                lowest_idx = y;
            }
        }
        if (lowest_idx != i) {
            int tmp = values[lowest_idx];
            values[lowest_idx] = values[i];
            values[i] = tmp;
        }
    }
    printf("\n");
    printf("Sorted values: ");
    for (int i = 0; i < length; i++) {
        printf("%d; ", values[i]);
    }
    printf("\n");
    printf("Type an integer number to search for: ");
    int query;
    scanf("%d", &query);
    // Binary search
    int from = 0;
    int to = length - 1;
    int steps = 0;
    while (from <= to) {
        steps++;
        // Divide search area into 2
        const int query_idx = from + ((to - from) / 2);
        if (values[query_idx] == query) {
            printf("Value %d was found at index %d after %d step(s).", query, query_idx, steps);
            printf("\n");
            exit(0);
        }
        printf("Index %d holds value %d", query_idx, values[query_idx]);
        printf("\n");
        if(values[query_idx] < query) {
            // Look for the upper area
            from = query_idx + 1;
        } else {
            // Look for the lower area
            to = query_idx - 1;
        }
    }
    printf("After %d step(s), value %d wasn't found.", steps, query);
    printf("\n");
}
