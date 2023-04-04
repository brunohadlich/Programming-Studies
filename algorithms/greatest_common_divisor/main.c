#include <stdio.h>
#include <stdlib.h>

int gcd(int n1, int n2) {
    int remainder = n1 % n2;
    while (remainder > 0) {
        n1 = n2;
        n2 = remainder;
        remainder = n1 % n2;
    }
    return n2;
}

int main(int argc, char *argv[]) {
    printf("Type the first number: ");
    int first_number;
    if (!scanf("%d", &first_number)) {
        printf("Invalid value. Exiting.");
        exit(1);
    }
    printf("Type the second number: ");
    int second_number;
    if (!scanf("%d", &second_number)) {
        printf("Invalid value. Exiting.");
        exit(1);
    }
    printf("Greatest common divisor: %d", gcd(first_number, second_number));
    exit(0);
}
