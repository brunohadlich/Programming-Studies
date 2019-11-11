#include <stdlib.h>
#include <stdio.h>

void slow() {
        char *v = malloc(100000000);
        int x, y;
        for (x = 0; x < 10000; x++) {
                for (y = x; y < 100000000; y+=10000) {
                        v[y] = v[y];
                }
        }
        free(v);
}

void fast() {
        char *v = malloc(100000000);
        int x, y;
        for (x = 0; x < 100000000; x += 10000) {
                int until = x + 10000;
                for (y = x; y < until; y++) {
                        v[y] = v[y];
                }
        }
        free(v);
}

int main() {
        fast();
}
