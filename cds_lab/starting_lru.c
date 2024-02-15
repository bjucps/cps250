/* CpS 250: C Data Structures Practice Lab
   completed by YOUR NAME (yourlogin)
   Spring THISYEAR
 */
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"  // userland rip of Linux kernel linked-list header (GPL2)

// object structure for tracking words in a LRU-cache
struct word {
	char *str;    // word contents (C string, NUL terminated; malloc'd)
	// TODO: additional fields as needed
};

// destroy/deallocate a `struct word` object completely
void word_free(struct word *wp) {
	if (wp) {	// if not-NULL pointer to word object...
		free(wp->str);	// free the string buffer...
		// TODO: any additional cleanup on the object
		free(wp);	// ...and free the struct object's memory, too
	}
}

int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	char *line_buf = NULL;	// buffer/size for reading lines
	size_t line_len = 0u;
	size_t cap = 0u;
	struct word *wp = NULL;	// used for finding/updating word objects

	if (argc < 2) {
		fprintf(stderr, "usage: %s CACHE_SLOTS\n", argv[0]);
		goto cleanup;
	}

	// strtoul has weird error semantics, so we need to muck directly with `errno`...	
	errno = 0;
	cap = strtoul(argv[1], NULL, 10);
	if (errno != 0) {
		perror("strtoul");
		goto cleanup;
	}

	// main input loop: read one word per line until EOF
	while (getline(&line_buf, &line_len, stdin) > 0) {
		// strip '\n' if present
		size_t len = strlen(line_buf);
		if (line_buf[len - 1] == '\n')
			line_buf[len - 1] = '\0';

		// find word in list if possible
		bool found = false;
		// TODO: look up word in LRU cache (found = true, wp = ptr-to-found-word)

		if (found) {	// cache hit! (wp points to cached word object)
			printf("%s: HIT\n", wp->str);
			// TODO: update LRU stats (wp points to most-recently-used word right now)
		} else {	// cache miss! (must add, and possibly evict)
			wp = malloc(sizeof(*wp));	// create node (assume no malloc-failures for simplicity)
			wp->str = strdup(line_buf);
			printf("%s: MISS\n", wp->str);
			// TODO: add this new word object into cache list (and, later, implement LRU eviction)
		}
	}
	if (ferror(stdin)) {
		perror("getline");
		goto cleanup;
	}
	puts("--------------------------------");
	puts("FINAL CACHE CONFIGURATION:");
	puts("--------------------------------");
	// TODO: print out final cache configuration (LRU order)
	

	ret = EXIT_SUCCESS;
cleanup:
	// TODO: clean up any other resources (e.g., the LRU lists/structures)
	free(line_buf);
	return ret;
}
