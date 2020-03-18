#include <stdio.h>

int count = 0;

void crash() {
    int result = 5 / count; // causes crash
}

int main(int argc, char **argv) {
    puts("Prepare to die!");
    crash();

    return 0;
}

