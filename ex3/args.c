// File: args.c
// Submitted by: 
//
// Build command: gcc -g args.c ex3_args_test.c -lbsd -oargs

#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

const int FILENAME_BUFSIZE = 10;
const int ERRMSG_BUFSIZE = 50;

// Validates command line arguments in <argv> and returns information extracted.
// On success, populates <infile>, <size>, and <help> with information
//   from args, sets <errmsg> to empty string, and returns 1. 
// On failure, sets <infile> to empty string, <size> to 0, and <help> to 0,
//   populates <errmsg> with an error message, and returns 0.
int parseArgs(int argc, char **argv, char infile[], long *size, int *help, char errmsg[])
{

    return -1;
}

