#include <string.h>

int main() {
	// literal strings goes into rodata (read onyl data) memory
	// causing segmentation fault in case you try to modify it
	char *msg = "abc\\x1fdef\\x1fghi\\x1fjkl";
	strcpy(msg, "as");
}
