#define _GNU_SOURCE	// must come FIRST
#include <stdio.h>
#include <string.h>

// includes for required constants/variables
#include <sched.h>
#include <sys/mount.h>

// Master list of named/symbolic constants we want to capture/print out (using the "X macros" pattern of code/data reuse)
// (add new constants as you discover that you need to know their numbers to pass them through ctypes)
// (REMEMBER: all but the last line of a multi-line macro needs to end with a trailing "line-continuation" backslash)
#define CONSTANTS \
	/* --- BEGIN LIST OF CONSTANTS (NO CHANGES before THIS LINE) --- */ \
	X(CLONE_NEWNS) \
	X(CLONE_NEWPID)	\
	/* --- END LIST OF CONSTANTS (NO CHANGES after THIS LINE) --- */

// Use the constant list to _define global variables for each_
#define X(name) int _##name = name;
CONSTANTS
#undef X

int main() {
	size_t max_width = 0u;
	char fmt[128];

	// Use the constant list to _find out how long the longest constant name was_
#define X(name) if (strlen(#name) > max_width) max_width = strlen(#name);
	CONSTANTS
#undef X

	// Construct a string format template embedding that length
	snprintf(fmt, sizeof fmt, "%%-%zus = 0x%%08x\n", max_width);	

	// Use the constant list to _print out all the variables as valid Python variable assignments_
#define X(name) printf(fmt, #name, _##name);
	CONSTANTS
#undef X
	return 0;
}
