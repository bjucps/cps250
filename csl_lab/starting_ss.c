#include <stdio.h>		// standard I/O (e.g., printf)
#include <string.h>		// standard C string functions (e.g., strlen, strchr)
#include <ctype.h>		// standard character-type/transform functions (e.g., isspace, toupper)

char *strip(char *s) {
	// TODO: return pointer to first non-whitespace char in `s`, AFTER modifying `s` to have no trailing whitespace, either
	return s;
}

int main(int argc, char **argv) {
	char buff[128];
	char *name = "";

	// Prompts for name (until non-empty, after stripping)
	printf("Please enter your name: ");
	name = strip(fgets(buff, sizeof(buff), stdin));
	while (strcmp(name, "") == 0) {
		printf("Please enter your name: ");
		name = strip(fgets(buff, sizeof(buff), stdin));
	}

	// TODO: replicate the name-length and first-initial tests

	// TODO: implement the search/split-on-space logic and print the appropriate question
	char *rest;
	printf("May I call you %s Q. %s?\n", name, rest);

}
