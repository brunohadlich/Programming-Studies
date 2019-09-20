#include <stdio.h>

inline int soma_multiplica(int a, int b, int c) {
	return a + b * c;
}

int main() {
	int a, b, c;
	scanf("%d", &a);
	scanf("%d", &b);
	scanf("%d", &c);
	printf("%d", soma_multiplica(a,b,c));
}
