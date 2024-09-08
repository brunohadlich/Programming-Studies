#include <string.h>

int main() {
	char *msg = "abc\\x1fdef\\x1fghi\\x1fjkl";
	strcpy(msg, "as");
}
