#include <stdio.h>		// standard I/O (e.g., printf, scanf)
#include <string.h>		// standard C string functions (and things like memcpy/memmove, too)

void
show_nums(int nums_arr[], int nums_len) {
	// TODO: replicate `show_nums` logic from `sl.py`
}

// No "tuples" in C--use an array of struct values instead
struct menu_item {
	char tag;
	char *name;
} menu_items[] = {
	{ .tag = 'a', .name = "Apples" },
	{ .tag = 'b', .name = "amBrosia" },
	{ .tag = 'c', .name = "aCorns" },
	{ .tag = '\0', .name = NULL },
};

int main(int argc, char **argv) {
	int nums[5] = { 1, 2, 3, 4 };	// allocate room for ONE extra value
	int nums_used = 4;

	// Show the initial list
	show_nums(nums, nums_used);

	// TODO: prompt the user for a number (`nval`) and the position to insert (`npos`)
	int nval, npos;

	// TODO: add checks that `npos` is valid (0 <= npos < 5), defaulting to "insert at end" if invalid

	// TODO: perform the "insertion" by hand (hint: memmove can help you safely copy all the elements that have to move)

	// Show the list of numbers after the change
	show_nums(nums, nums_len);

	// TODO: print out a menu of all the valid `menu_items` (hint, that `\0`/NULL record tells you when to stop)

	// Prompt the user for a single character of input
	char choice;
	printf("> ");
	scanf(" %c", &choice);	// FUN experiment (not really): remove the leading space before %c in there and see what happens...
	
	// TODO: find the selected option (or not) in the list of `menu_items`	

	// TODO: scold or acknowledge the user's choice (just like in `sl.py`)	
	
	// We always "succeed"	
	return 0;
}
