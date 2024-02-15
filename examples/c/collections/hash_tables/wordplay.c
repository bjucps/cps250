/* CpS 250: UThash and UTstring demo program
   by Dr. J
   (c) 2024 Bob Jones University
 */
   
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "utstring.h"
#include "uthash.h"

// hashtable entry: a record of a substitution rule: name and value
struct sub {
	UT_string name;		// utstring (in-place) holding substitution name
	UT_string value;	// utstring (in-place) holding substitution value
	UT_hash_handle hh;	// uthash handle (internal book-keeping for a hashtable)
};

// Read a '\n'-delimited line from a FILE* `stream`, appending onto utstring `s`
// Returns 0 on success, 1 on EOF, and -1 on non-EOF error
//
// "Success" scenarios:
// * read zero or more characters and then encountered '\n'
// * read at least one non-'\n' character and then encountered EOF
// (i.e., EOF counts as a line-terminator IFF the "line" is non-empty)
int
utstring_getline(UT_string *s, FILE *stream) {
	utstring_clear(s);
	int ch = -1;

	while ((ch = fgetc(stream)) != EOF && (ch != '\n')) {
		utstring_printf(s, "%c", ch);
	}
	if (ch == EOF) {
		if (feof(stream)) {		// "error" caused by EOF...
			return utstring_len(s) == 0;	// non-zero (true) if empty EOF-line
		} else {
			// true error
			return -1;
		}
	} else {
		return 0;
	}
}

// Parse a substitution assignment rule from `s` of the form ":NAME=VALUE" and add (or update!) to `subs`
// Return 0 on success, -1 on failure
int
parse_sub_rule(UT_string *s, struct sub **subs) {
	int ret = -1;
	struct sub *new_sub = NULL;
	int eq_pos = -1;

	// sanity checks (shorter than shortest possible, doesn't start with ':', no/bad '=')
	// (finds the '=' position, if there is one; MUST be > 1 to have a value NAME)
	if ((utstring_len(s) < 4)
			|| (utstring_body(s)[0] != ':')
			|| ((eq_pos = utstring_find(s, 0, "=", 1)) < 2)) goto cleanup;
	
	// quality check (name substring contains no '}'
	for (int i = 1; i < eq_pos; ++i) {
		if (utstring_body(s)[i] == '}') goto cleanup;
	}

	// find an existing sub object by our name, if possible
	char *namep = utstring_body(s) + 1;
	size_t namelen = eq_pos - 1;
	HASH_FIND(hh, *subs, namep, namelen, new_sub);

	// found one!
	if (new_sub != NULL) {
		// remove it from the hash table (cannot modify a key in-place)...
		HASH_DELETE(hh, *subs, new_sub);

		// reset the utstring objects
		utstring_clear(&new_sub->name);
		utstring_clear(&new_sub->value);
	} else {
		// didn't find one; allocate a new one
		if ((new_sub = malloc(sizeof(struct sub))) == NULL) {
			perror("malloc");
			goto cleanup;
		}

		// and get some buffers allocated from the utstrings
		utstring_init(&new_sub->name);
		utstring_init(&new_sub->value);
	}

	// copy the name string out
	// (use bincpy, since NAME is not 0-terminated)
	utstring_bincpy(&new_sub->name, namep, namelen);

	// copy the value string out
	// (use printf-concatenation, since VALUE _is_ 0-terminated and we don't need a span)
	// (VALUE string starts at 1 past `eq_pos`)
	utstring_printf(&new_sub->value, "%s", utstring_body(s) + eq_pos + 1);

	// insert this name/value pair into the hash table using NAME as the key
	HASH_ADD_KEYPTR(hh, *subs, utstring_body(&new_sub->name), utstring_len(&new_sub->name), new_sub);
	new_sub = NULL;	// "release" ownership of this now that it's in the hashtable
	
	ret = 0;
cleanup:
	if (new_sub) {
		// we still have ownership and need to free it all
		utstring_done(&new_sub->value);
		utstring_done(&new_sub->name);
		free(new_sub);
	}
	return ret;
}

// Scan a NUL-terminated string from `start` to identify a substitution token
// Returns NULL on syntax error, or a pointer to the next char AFTER the token
// On success, sets `*name_start` to the start of the actual token name and
//	`*name_len` to the length of the token name in characters.
char *
scan_sub_token(char *start, char **name_start, size_t *name_len) {
	char *ret = NULL;
	char *cp = start;

	if (!*cp) goto cleanup;

   	if (*cp == '{') {
		for (++cp; *cp && (*cp != '}'); ++cp);
		if (*cp != '}') goto cleanup;
		*name_start = start + 1;
		*name_len = cp - *name_start;
		ret = cp;
	} else {
		for (++cp; *cp && isalnum(*cp); ++cp);
		*name_start = start;
		*name_len = cp - start;
		ret = --cp;
	}
cleanup:
	return ret;
}



// Read '\n' delimited lines from STDIN until EOF.
// Parse lines of the form ":NAME=VALUE" as "substitution definition rules" (stored in a hash table keyed by NAME)
// Regurgitate all other lines back to STDOUT with "$NAME" substituted with the corresponding VALUE from the hashtable (if any)
int
main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	struct sub *subs = NULL;	// used as the head/handle to the entire hash table of substitutions
	UT_string *line = NULL;		// use indirect utstring (one-time cost for extra malloc)

	// Create/allocate for utstring used for line input
	utstring_new(line);

	// While reading a line results in no error/EOF...	
	while (!utstring_getline(line, stdin)) {
		// If the string starts with ':'...
		if (utstring_len(line) > 0 && utstring_body(line)[0] == ':') {
			if (parse_sub_rule(line, &subs)) {
				fprintf(stderr, "syntax error: '%s'\n", utstring_body(line));
				goto cleanup;
			}
		} else {
			// otherwise, copy this line to STDOUT _with substitutions performed_
			for (char *cp = utstring_body(line); *cp; ++cp) {
				// is this a substitution marker?
				if (*cp == '$') {
					char *namep;
					size_t namelen;
					// scan the name and determine where we should resume on the other side
					if ((cp = scan_sub_token(cp + 1, &namep, &namelen)) == NULL) {
						fprintf(stderr, "syntax error: expected NAME after '$': '%s'\n", utstring_body(line));
						goto cleanup;
					}

					// so the string from `namep` up to `namep+namelen` is our NAME to search for...
					struct sub *sr = NULL;
					HASH_FIND(hh, subs, namep, namelen, sr);
					if (sr == NULL) {
						namep[namelen] = '\0';	// destructively NUL-terminate, just so we can print our error and bail out
						fprintf(stderr, "name error: no such name '%s'\n", namep);
						goto cleanup;
					} else {
						// FINALLY! lets print out the value (NUL-terminated)
						fputs(utstring_body(&sr->value), stdout);
					}
				} else {
					// no, not a substitution marker; just print it out
					putchar(*cp);
				}
			}
			putchar('\n');
		}
	}

	ret = EXIT_SUCCESS;
cleanup:
	// In whatever state we ended, free all our remaining allocated resources
	if (subs) {
		bool should_print = (getenv("DEBUG") != NULL);
		struct sub *s, *tmp;
		HASH_ITER(hh, subs, s, tmp) {
			if (should_print) {
				fprintf(stderr, "DEBUG: %s=%s\n", utstring_body(&s->name), utstring_body(&s->value));
			}
			HASH_DELETE(hh, subs, s);
			utstring_done(&s->value);
			utstring_done(&s->name);
			free(s);
		}
	}
	utstring_free(line);
	return ret;
}
