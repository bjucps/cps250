#include <stdio.h>
#include <assert.h>
#include <bsd/string.h>

#include "uthash.h"

#define NAMECAP 32

/* inline-key/value hash item */
struct inkeyval {
	char name[NAMECAP];
	int value;
	UT_hash_handle hh;
};

/* external-key/value hash item */
struct exkeyval {
	char *name;
	int value;
	UT_hash_handle hh;
};

// note: we pass a pointer-to-pointer-to-type so that the HASH_XXX macros can _update_
//       the pointer-to-type that acts as a handle to the hash table (see the uthash user guide)
struct inkeyval *add_inkeyval(struct inkeyval **ht, char *the_name, int the_value) {
	struct inkeyval *node = malloc(sizeof(struct inkeyval));
	strlcpy(node->name, the_name, sizeof(node->name));
	node->value = the_value;

	// note: "name" here is a _field_ name (this is a _macro_)
	// also note: HASH_ADD_STR is a "convenience" macro that _assumes_ the hash-handle field is `hh`
	HASH_ADD_STR(*ht, name, node); 
	return node;
}

struct exkeyval *add_exkeyval(struct exkeyval **ht, char *the_name, int the_value) {
	struct exkeyval *node = malloc(sizeof(struct exkeyval));
	node->name = strdup(the_name); // heap allocation--must free later
	node->value = the_value;
	
	// note: HASH_ADD_KEYPTR required when we don't have an _array_ field (we give a pointer _value_ and a length _value_)
	// also note: HASH_ADD_KEYPTR is a "general" macro that requires you to give the hash-handle field name, too
	HASH_ADD_KEYPTR(hh, *ht, node->name, strlen(node->name), node);
	return node;
}

int main(int argc, char **argv) {
	// make hash table 1 (nodes storing key string _objects_ via inline char arrays)
	struct inkeyval *hashin = NULL;
	struct inkeyval *ikv1 = add_inkeyval(&hashin, "apple", 42);
	struct inkeyval *ikv2 = add_inkeyval(&hashin, "banana", 1337);

	// make hash table 2 (nodes storing key string _values_ via char pointers to heap allocations)
	struct exkeyval *hashex = NULL;
	struct exkeyval *ekv1 = add_exkeyval(&hashex, "cherry", 1010);
	struct exkeyval *ekv2 = add_exkeyval(&hashex, "date", 1776);

	// search for inline/external key values
	struct inkeyval *ikp = NULL;
	HASH_FIND_STR(hashin, "apple", ikp);	// SHOULD find
	assert(ikp != NULL);
	assert(ikp == ikv1);
	HASH_FIND_STR(hashin, "cherry", ikp);	// should NOT find
	assert (ikp == NULL);

	// let the user affect the next search test with CLI argument[s]
	char *search = "banana";
	if (argc > 1) {
		search = argv[1];
		printf("You gave me %d arguments, so ", argc - 1);
	} else {
		printf("You gave me no arguments, so ");
	}
	printf("I'll use '%s' as the search word.\n", search);

	// search hash table 2
	struct exkeyval *ekp = NULL;
	HASH_FIND_STR(hashex, search, ekp);  // HASH_FIND_STR works for both kinds of key string, unlike HASH_ADD_STR
	if (ekp) {
		printf("I found %s (%d)!\n", ekp->name, ekp->value);
	} else {
		printf("I found nothing...\n");
	}

	// demonstrate iteration and item deletion to dump/cleanup both hash tables
	// (need a "tmp" pointer so that the loop is deletion-safe)
	struct inkeyval *itmp;
	HASH_ITER(hh, hashin, ikp, itmp) {
		HASH_DEL(hashin, ikp);
		printf("hashin['%s'] = %d (deleted)\n", ikp->name, ikp->value);
		free(ikp);
	}
	struct exkeyval *etmp;
	HASH_ITER(hh, hashex, ekp, etmp) {
		HASH_DEL(hashex, ekp);
		printf("hashex['%s'] = %d (deleted)\n", ekp->name, ekp->value);	// TODO: figure out Roman Numeral output
		free(ekp->name); // remember strdup?
		free(ekp);
	}

	return 0;
}
