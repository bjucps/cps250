#include <stdio.h>
#include <bsd/string.h>

void crashme() {
    char *buf = NULL;
    strlcpy(buf, "Hello", sizeof(buf)); // crash!
}

int main(int argc, char **argv) {

    puts("Prepare to die!");
    crashme();
    return 0;
}

