#include <stdio.h>		// standard I/O (e.g., printf, scanf)
#include <string.h>		// standard C string functions (and things like memcpy/memmove, too)

void show_nums(int nums_arr[], int nums_len) {
	// TODO: replicate `show_nums` logic from `sl.py`
}

void yolo_remove_element(int nums_arr[], int *nums_len, int index) {
	// TODO: modify `nums_arr` contents to eliminate element `index` and decrement `*nums_len`
	// (hint 1: this function does NOT have to ensure `index` is valid, as the main program does that)
	// (hint 2: memmove can help you safely copy all the elements that have to move)
}

void yolo_insert_element(int nums_arr[], int *nums_len, int index, int value) {
	// TODO: modify `nums_arr` contents to make room for `value` at slot `index`, and increment `*nums_len`
	// (see yolo_remove_element hints here, too)
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
	int nums[4] = { 1, 2, 3, 4 };
	int nums_used = 4;

	// Show the initial list
	show_nums(nums, nums_used);

	// TODO: prompt the user for a position to remove (`npos`)
	int npos;

	// TODO: add checks that `npos` is valid (0 <= npos < nums_used), defaulting to "remove element 0" if invalid

	// Update `nums` to remove the element at `npos` (and update `nums_used`)
	yolo_remove_element(nums, &nums_used, npos);

	// TODO: prompt the user for a number (`nval`) and the position to insert (`npos`)
	int nval;

	// TODO: add checks that `npos` is valid (0 <= npos <= nums_used), defaulting to "insert at end" if invalid
	// (yes, now npos == nums_used is OK, as it means "insert" it at the end, after expanding `nums_used`)

	// Update `nums` to make room for `nval` at location `npos` (and update `nums_used`)
	yolo_insert_element(nums, &nums_used, npos, nval);

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
