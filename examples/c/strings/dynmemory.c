// Compile:
// gcc -g -odynmemory -Wall -Werror dynmemory.c -lbsd

#include <stdio.h>
#include <stdlib.h>     // Need this for malloc/free
#include <bsd/string.h>  // strlcpy/strlcat

int main() {
    char *buff = malloc(256);   // Room for 255+1 char C string (uninitialized; random junk)

    // malloc() returns NULL if it cannot allocate for some reason
    if (buff == NULL) {
        perror("unable to allocate buffer for example program");
        exit(1);
    }

    strlcpy(buff, "hello, world!", 256);

    printf("This is the message: '%s'\n", buff);

    // What you malloc() you must also free()!
    // (Valgrind is your friend...)
    free(buff);

    return 0;
}

