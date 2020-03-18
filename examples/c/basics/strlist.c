// strlist
// A comparison of 2 approaches to arrays-of-C-strings: multidimension char arrays and char pointer arrays
// (c) 2016, Bob Jones University
#include <stdio.h>

// 2-dimension grid of chars (5 consecutive arrays of 20 chars each)
// The initializers copy data into strlist1 itself
char strlist1[][20] = { "ape", "bat", "cat", "dog", "emu" };

// 1-dimension array of char pointers (5 consecutive pointers to C strings)
// The initializers are not copied into strlist2; rather, strlist2's pointers
// hold the addresses at which the initializer string literals live
char *strlist2[] = { "ape", "bat", "cat", "dog", "emu" };

int main() {
    printf("strlist1[0] == '%s'\n", strlist1[0]);

    printf("strlist2[1] == '%s'\n", strlist2[1]);
}
