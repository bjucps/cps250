#include <stdio.h>
#include <stdlib.h>     // Need this for malloc/free

int alloc_memory()
{
    char *buff = malloc(256);   // Room for 255+1 char C string (uninitialized; random junk)

    // malloc() returns NULL if it cannot allocate for some reason
    if (buff == NULL) {
        perror("unable to allocate buffer for example program");
        exit(1);
    }

    // use the memory somehow

    // oops - we forgot to deallocate
}
   

int main() {
  alloc_memory();
}

