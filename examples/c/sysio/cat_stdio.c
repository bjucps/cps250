#include <stdio.h>


int main(int argc, char **argv) {
    int ret = 1;

    FILE *stream = fopen(argv[1], "r");
    if (!stream) {
        perror("unable to open file");
        goto cleanup;
    }

    char c = '\0';
    while ((c = fgetc(stream)) != EOF) {
        putchar(c);
    }

    ret = 0;
cleanup:
    if (stream) fclose(stream);
    return ret;
}
