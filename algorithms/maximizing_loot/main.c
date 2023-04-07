// Greedy algorithm 'maximizing loot' that solves the fractional knapsack problem.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("How much weight the backpack can carry in kg? ");
    float capacity;
    if (!scanf("%f", &capacity)) {
        printf("Invalid value. Exiting.");
        exit(1);
    }
    printf("How many items exist? ");
    int n_items;
    if (!scanf("%d", &n_items)) {
        printf("Invalid value. Exiting.");
        exit(1);
    }
    int i;
    float *weights = (float *)malloc(sizeof(float) * n_items);
    float *values = (float *)malloc(sizeof(float) * n_items);
    float packpack_value = 0;
    for (i = 0; i < n_items; i++) {
        printf("What is the weight of item %d in kg? ", i + 1);
        if (!scanf("%f", &weights[i])) {
            printf("Invalid value. Exiting.");
            exit(1);
        }
        printf("What is the value of item %d in US$? ", i + 1);
        if (!scanf("%f", &values[i])) {
            printf("Invalid value. Exiting.");
            exit(1);
        }
    }
    while (capacity > 0) {
        int idx_most_valuable = 0;
        for (i = 0; i < n_items; i++) {
            if (weights[i] > 0 && (values[i] / weights[i]) > (values[idx_most_valuable] / weights[idx_most_valuable])) {
                idx_most_valuable = i;
            }
        }
        if (capacity > weights[idx_most_valuable]) {
            packpack_value += values[idx_most_valuable];
            capacity -= weights[idx_most_valuable];
            printf("Added %fkg of item %d\n", weights[idx_most_valuable], idx_most_valuable + 1);
            weights[idx_most_valuable] = 0;
        } else {
            packpack_value += (capacity / weights[idx_most_valuable]) * values[idx_most_valuable];
            printf("Added %fkg of item %d\n", capacity, idx_most_valuable + 1);
            capacity = 0;
            weights[idx_most_valuable] -= capacity;
        }
    }
    printf("Backpack total value: US$%f\n", packpack_value);
    return 0;
}
