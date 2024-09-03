// This comment will be stripped off after pre-processing step

// defined IO as <stdio.h>
#define IO <stdio.h>
// this is called computed include, it will first expand IO into <stdio.h> and then include it
#include IO

// char str1[] = "abc def";
char str1[] = "abc"
                    " def";

// char str2[] = "abc                    def";
char str2[] = "abc\
                    def";

#define print_str(value) printf("%s\n", value)

#define NUMBERS_LENGTH 3
// NUMBERS1 = 1, 2, 3
#define NUMBERS1 1, 2, 3
// NUMBERS2 = 4, 5, 6
#define NUMBERS2 4, \
                 5, \
                 6

int main(int argc, char *argv[]) {
    print_str(str1); // printf("%s\n", str1)
    print_str(str2); // printf("%s\n", str2)
    int numbers1[] = { NUMBERS1 }; // int numbers1[] = { 1, 2, 3 };
    for (int i = 0; i < NUMBERS_LENGTH; i++) { // for (int i = 0; i < 3; i++) {
        printf("%d\n", numbers1[i]);
    }
    int numbers2[] = { NUMBERS2 }; // int numbers1[] = { 4, 5, 6 };
    for (int i = 0; i < NUMBERS_LENGTH; i++) { // for (int i = 0; i < 3; i++) {
        printf("%d\n", numbers2[i]);
    }

    #define PRINT_FOO
    #ifdef PRINT_FOO
    print_str("foo"); // will run because PRINT_FOO is defined
    #else
    print_str("bar");
    #endif

    #undef PRINT_FOO
    #ifdef PRINT_FOO
    print_str("foo");
    #else
    print_str("bar"); // will run because PRINT_FOO is NOT defined
    #endif

    #define FIVE 5
    #if FIVE > 3 // first expands FIVE to 5 and then evaluate 5 > 3
    print_str("5 > 3");
    #else
    print_str("5 is not greater than 3");
    #endif

    #if defined XPTO || defined FIVE
    print_str("One of XPTO or FIVE is defined");
    #endif

    printf("%d\n", __LINE__);
}
