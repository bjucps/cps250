#ifndef READBLAH_H
#define READBLAH_H

#include <stdio.h>

// opens <filename> and returns a FILE * for reading, or
// NULL if no such file exists or the file is not a blah file.
FILE *open_blah(char *filename);

// reads a line of text from <f> and returns it
// caller is responsible for deallocating the pointer
// returns NULL on EOF or error
char *read_blah(FILE *f);

// Closes <f>
void close_blah(FILE *f);


#endif
