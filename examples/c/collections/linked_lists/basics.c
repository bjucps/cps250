#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// the Linux kernel linked list types/macros/functions (GPL2)
#include "list.h"

// demo list node type
struct node {
	char *name;
	struct list_head entry;
};


int main(int argc, char **argv) {
	// declare/initialize empty list handle
	LIST_HEAD(food);

	// confirm empty	
	assert(list_empty(&food));

	// first object to add (can allocate any way you like)
	struct node pizza = {
		.name = "pizza",
		.entry = LIST_HEAD_INIT(pizza.entry)	// initialize <entry> to "empty" (not on list); N.B.: _not_ "INIT_LIST_HEAD"!!
	};

	// append to list
	list_add_tail(&pizza.entry, &food); // quiz: what happens if you pass `&pizza` instead?

	struct node ice_cream = {
		.name = "ice cream",
		.entry = LIST_HEAD_INIT(ice_cream.entry)
	};
	list_add_tail(&ice_cream.entry, &food);

	puts("iterating over list...");
	struct list_head *pos = NULL;	// N.B.: a `struct list_head *`, not a `struct node *`!!
	list_for_each(pos, &food) {
		// MACRO MAGIC: get a `struct node *` from a `struct list_head *` based on struct field layout
		struct node *np = list_entry(pos, struct node, entry);
		printf("node: %s @ %p (.entry @ %p)\n", np->name, np, pos);
	}
	puts("DONE");

	// demo dynamic struct allocation (don't forget to free!)
	struct node *candyp = malloc(sizeof(struct node));
	candyp->name = "candy";
	INIT_LIST_HEAD(&candyp->entry); // N.B. _not_ LIST_HEAD_INIT this time! (this is imperative, not declarative)

	// can insert at head of list
	list_add(&candyp->entry, &food);

	// can also insert before/after to a given node
	struct node steak = {
		.name = "BEEF",
		.entry = LIST_HEAD_INIT(steak.entry)
	};
	list_add(&steak.entry, &candyp->entry);	// after "candy", before "pizza" (why not `list_add_tail`??)

	// "for-each with list-entry" is such a common pattern that there's a dedicated macro for it:
	puts("once more, with FEELING:");
	struct node *np = NULL;
	list_for_each_entry(np, &food, entry) { // "entry" here is a _field name_ (MACRO, not function)
		printf("node: %s @ %p (.entry @ %p)\n", np->name, np, &np->entry);
	}
	puts("done again");

	// lets delete the dynamically allocated node (make sure to remove it from the linked-list first!)
	list_del(&candyp->entry);      // pop-quiz: what would happen (or *could* happen) if we left this line out?
	free(candyp);                  // experiment: comment out this line, do `make debug`, and try running again

	// one last run through the list...
	puts("one last time, without our dynamic friend:");
	list_for_each_entry(np, &food, entry) { 
		printf("node: %s @ %p (.entry @ %p)\n", np->name, np, &np->entry);
	}
	puts("done again");

	return EXIT_SUCCESS;
}
