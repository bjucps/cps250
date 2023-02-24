#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(char *input, char *delims) {
	char **ret = NULL;
	char *save = NULL; 
	char *tok = strtok_r(input, delims, &save), *last_tok = NULL;
	int slot = 0, num_slots = 4;
	char **slotbuf = calloc(sizeof(char *), num_slots);
	if (tok == NULL) goto cleanup;
	if (slotbuf == NULL) goto cleanup;

	do {
		if (slot == num_slots) {
			num_slots *= 2;
			if ((slotbuf = realloc(slotbuf, num_slots * sizeof(char *))) == NULL) {
				goto cleanup;
			}
		}
		slotbuf[slot++] = tok;
		last_tok = tok;
		tok = strtok_r(NULL, delims, &save);
	} while (last_tok != NULL);

	ret = slotbuf;
	slotbuf = NULL;
cleanup:
	free(slotbuf);
	return ret;
}


int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "usage: %s STRING_TO_SPLIT DELIMS_TO_USE\n", argv[0]);
		exit(1);
	}

	char **words = split(argv[1], argv[2]);
	if (!words) {
		printf("split failed!\n");
		exit(1);
	}

	for (int i = 0; words[i] != NULL; ++i) {	
		printf("words[%d] = '%s'\n", i, words[i]);
	}
	free(words);
	return 0;
}
