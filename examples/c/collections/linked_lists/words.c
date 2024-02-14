/* CpS 250 Examples: words: a part-of-speech game demonstrating multiple-linked-lists
   by Dr. J
   (c) 2024, Bob Jones University
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <bsd/string.h>

#include "list.h" // userland rip of Linux kernel linked-list head (GPL2)

// we can deal with a max-word-size here; if not, we'd have to use heap buffers/fat pointers...
#define WORD_BUF_SIZE 32

struct word {
	char str[WORD_BUF_SIZE];		// fixed-size storage for words (to avoid complexity in an example program)
	struct list_head word_entry;	// list #1: global words list
	struct list_head part_entry;	// list #2: per-part-of-speech list
};

// declare/initialize all our lists (empty) globally, for convenience
LIST_HEAD(all_words);
LIST_HEAD(all_nouns);
LIST_HEAD(all_verbs);
LIST_HEAD(all_adjs);
LIST_HEAD(all_advs);

// also declare counters for each list (to track size)
size_t num_words = 0u;
size_t num_nouns = 0u;
size_t num_verbs = 0u;
size_t num_adjs = 0u;
size_t num_advs = 0u;

// utility data: mapping part-of-speech name to list head
// (defines "part_list_map", which is an array of 
// "struct part_list_map_entry" objects combining string/list-head ptr)
struct part_list_map_entry {
	char *name;
	struct list_head *head;
	size_t *counter;
} part_list_map[] = {
	{ "noun", &all_nouns, &num_nouns },
	{ "verb", &all_verbs, &num_verbs },
	{ "adjective", &all_adjs, &num_adjs },
	{ "adverb", &all_advs, &num_advs },
	{ NULL, NULL, NULL},	// terminate the list with all-NULLs
};

// utility function: look up a part-of-speech list (and counter) by name
struct list_head *part_list(char *part_name, size_t **ctr_ptr) {
	// iterate over the mapping array until we get a NULL ->name member
	for (struct part_list_map_entry *plme = part_list_map; plme->name; ++plme) {
		if (strcmp(plme->name, part_name) == 0) {
			// found it!
			if (ctr_ptr) *ctr_ptr = plme->counter; // use ptr-to-counter IFF given
			return plme->head; // return ptr-to-list-head
		}
	}

	// failure...
	return NULL;
}

// utility function: print out all lists to show the various word orders
// (every word is on two lists: the all-words global list and exactly one "part-of-speech" list;
// each list, though, has its own sequence/order, independent of the others)
void dump_lists() {
	struct word *wp;
	printf("ALL:");
	list_for_each_entry(wp, &all_words, word_entry) // this is the only list using the `word_entry` field
		printf(" %s", wp->str);
	
	for (struct part_list_map_entry *plme = part_list_map; plme->name; ++plme) {
		printf("\n%s:", plme->name);
		list_for_each_entry(wp, plme->head, part_entry) // all the part-of-speech lists use the `part_entry` field
			printf(" %s", wp->str);
	}
	putchar('\n');
}


int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	struct word *cwp = NULL, *ctemp = NULL;
	char *line_buf = NULL;
	size_t line_len = 0u;
	
	// read lines until EOF (or error)
	while (getline(&line_buf, &line_len, stdin) > 0) {
		// on blank line: break out and advance to the next part
		if (strcmp(line_buf, "\n") == 0) break;

		// tokenize on ":" to find the part-of-speech
		char *cont = NULL, *wstr = NULL;
		char *part = strtok_r(line_buf, ":", &cont);

		// look up that list (and its counter)
		size_t *pcounter = NULL;
		struct list_head *plist = part_list(part, &pcounter);
		if (!plist) {
			// oops, no such part of speech! 
			printf("no such part-of-speech '%s'\n", part);

			// skip to the next line
			continue;
		}

		// now parse the rest of the line for white-space delimited words
		while ((wstr = strtok_r(NULL, " \t\r\n", &cont)) != NULL) {
			// create a word object, assuming no malloc failures
			// [warning: malloc-per-object is not efficient in most "real-world" program, but we do it here for simplicity]
			struct word *wp = malloc(sizeof(struct word));
			strlcpy(wp->str, wstr, sizeof wp->str);
			INIT_LIST_HEAD(&wp->word_entry);
			INIT_LIST_HEAD(&wp->part_entry);

			// add it to the global all-words list (and count it)
			list_add_tail(&wp->word_entry, &all_words);
			++num_words;

			// and to the specific part-of-speech list (and count it)
			list_add_tail(&wp->part_entry, plist);
			++(*pcounter);
		}
	}
	if (ferror(stdin)) { // catch any errors that aborted the loop
		perror("getline");
		goto cleanup;
	}

	// print out the total/per-part-of-speech counts
	printf("read %zu total words (", num_words);
	for (struct part_list_map_entry *plme = part_list_map; plme->name; ++plme) {
		printf("%zu of part '%s'", *(plme->counter), plme->name);

		// hacky code to produce nicer output: is the next name NULL?
		// (if so, that means we're the LAST element of the mapping list)
		if ((plme + 1)->name == NULL) {
			fputs(")\n", stdout);
		} else {
			fputs(", ", stdout);
		}
	}
	puts("\nINITIAL LIST ORDERS:");
	dump_lists();
	puts("\nenter next-word requests, one per line; EOF to end (e.g., \"word\", \"noun\", etc.)");

	// read lines until EOF (or error)
	while (getline(&line_buf, &line_len, stdin) > 0) {
		struct list_head *lh = NULL;
		// strip newline (if any)
		size_t llen = strlen(line_buf);
		if (line_buf[llen - 1] == '\n') {
			line_buf[llen - 1] = '\0';
		}

		// handle word-type request by 
		// - identifyint the correct list to use
		// - printing the first word in that list
		// - moving that first word to the "tail" of that list
		if (strcmp(line_buf, "word") == 0 && !list_empty(&all_words)) {
			// is this a request for "word" (i.e., no part-of-speech)?
			// if so, use the global word list
			struct word *wp = list_entry(all_words.next, struct word, word_entry);
			puts(wp->str);
			list_move_tail(&wp->word_entry, &all_words);
		} else if ((lh = part_list(line_buf, NULL)) != NULL && !list_empty(lh)) {
			// did it match a non-empty part of speech?
			// use that part list
			struct word *wp = list_entry(lh->next, struct word, part_entry);
			puts(wp->str);
			list_move_tail(&wp->part_entry, lh);
		} else {
			// otherwise complain and ignore this line
			printf("ERROR: no %ss on file\n", line_buf);
		}
	}
	if (ferror(stdin)) {
		perror("getline");
		goto cleanup;
	}

	// print out the final list-sequences to help us understand what was happening
	puts("\nFINAL LIST ORDERS:");
	dump_lists();

	ret = EXIT_SUCCESS;
cleanup:
	free(line_buf);

	// iterate the all-words list ("safe" so we can delete items)...
	list_for_each_entry_safe(cwp, ctemp, &all_words, word_entry) {
		// remove from the global word list
		list_del(&cwp->word_entry);

		// and from whatever part-of-speech list it was on
		list_del(&cwp->part_entry);

		// and free its memory!
		free(cwp);
	}
	return ret;
}
