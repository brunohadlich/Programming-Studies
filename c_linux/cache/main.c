#include <stdlib.h>
#include <stdio.h>

void slow() {
        char *v = malloc(100000000);
        int x, y, k = 0;
        for (x = 0; x < 10000; x++) {
                for (y = x; y < 100000000; y+=10000) {
			k++;
                        v[y] = v[y];
                }
        }
	printf("Iterated: %d times.\n", k);
        free(v);
}

void fast() {
        char *v = malloc(100000000);
        int x, y, k = 0;
        for (x = 0; x < 100000000; x += 10000) {
                int until = x + 10000;
                for (y = x; y < until; y++) {
			k++;
                        v[y] = v[y];
                }
        }
	printf("Iterated: %d times.\n", k);
        free(v);
}

void very_fast() {
        char *v = malloc(100000000);
        int x, y, k = 0;
        for (x = 0; x < 100000000; x += 10000) {
                int until = x + 10000;
                for (y = x; y < until; y++) {
			k++;
                        v[0] = v[0];
                }
        }
	printf("Iterated: %d times.\n", k);
        free(v);
}

int main() {
        //slow();
        //fast();
	very_fast();
}
