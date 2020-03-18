#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern unsigned int crunch(unsigned char *buff, unsigned int blen);

int main(int argc, char **argv) {
    int ret = 1;

    unsigned char *buff = NULL;
    FILE *stream = NULL;

    if (argc < 2) {
        puts("usage: crunch FILENAME");
        goto cleanup;
    }


    struct stat info = { 0 };
    if (stat(argv[1], &info)) {
        perror("stat");
        goto cleanup;
    }

    buff = malloc(info.st_size);
    if (!buff) {
        perror("malloc");
        goto cleanup;
    }

    stream = fopen(argv[1], "rb");
    if (!stream) {
        perror("fopen");
        goto cleanup;
    }

    if (fread(buff, sizeof(char), info.st_size, stream) < info.st_size) {
        perror("fread");
        goto cleanup;
    }

    unsigned int hash = crunch(buff, info.st_size);
    printf("%s: 0x%08x\n", argv[1], hash);

    ret = 0;
cleanup:
    if (stream) { fclose(stream); }
    free(buff);
    return ret;
}

