// buffer_overrun.c
// - Demonstrates what happens when a function assumes the array is large enough
//   to hold the data it writes to it

// For better crash diagnostics do one of the following:

// 1. Compile with -g and run with valgrind:
//    gcc -g buffer_overrun.c -obo
//    valgrind ./bo
// 2. Compile with additional gcc flags:
//    gcc -fsanitize=address -g -fno-omit-frame-pointer buffer_overrun.c -obo

#include <stdio.h>
#include <string.h>

int overrun(char *buf)
{
  strcpy(buf, "hahahahahaha"); // uh oh - attempting to write too much data into buf
}

int main()
{
  char buf[6];
  puts("Getting ready to die!");
  overrun(buf);

}
