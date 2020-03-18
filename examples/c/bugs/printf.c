#include <stdio.h>

int main(int argc, char **argv) {
    char fname[40];

    if (argc != 2) return 1;

    snprintf(fname, sizeof(fname), "/tmp/%s\n", argv[1]);
    printf(fname);

    return 0;
}

