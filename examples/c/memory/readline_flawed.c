#include <stdio.h>

// Read a line of text from STDIN and return a pointer to the resulting C string
char *readline() {
    char buffer[80];

    // Use stdio library routine to read a line
    // of text into <buffer> from STDIN
    fgets(buffer, sizeof(buffer), stdin);

    // Return pointer to <buffer>
    return buffer;
}

int main()
{
  char *buf = readline();
  printf("Hello, %s\n", buf);
}

