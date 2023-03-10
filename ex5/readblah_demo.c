#include <stdio.h>
#include <stdlib.h>
#include "readblah.h"


int main(int argc, char **argv) {
	FILE *f;
	char *data;

	if (argc == 2) {
		f = open_blah(argv[1]);
		if (!f) {
			puts("No such file, or not a blah file.");
			exit(1);
		}            
		data = read_blah(f);
		while (data != NULL) {
			puts(data);
			free(data);
			data = read_blah(f);
		}
		close_blah(f);
	}
}
