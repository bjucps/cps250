#include <stdio.h>
#include <stdlib.h>     // Need this for malloc/free
#include <bsd/string.h>

char *junk()
{
    char buf[80] = "Hello world\n";

    return buf;

}

int main()
{
    char buf[10];

    strcpy(buf, "abcdefghij");

    char *result = junk();
    printf("%s\n", result);

}
