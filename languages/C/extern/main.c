#include <stdio.h>
#include "extern_foo.h"

int main(int argc, char *argv[]) {
    // foo is declared in extern.h and defined and initialized in extern.c
    printf("%d\n", foo);
}
