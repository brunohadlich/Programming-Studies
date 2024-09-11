#include <stdio.h>

int main() {
	char string[10];
	int a = 7;

	printf("Input more than 10 characters to cause 'stack smashing' error.\n");
	scanf("%s" , string);

	printf("a: %d\n", a);
}
