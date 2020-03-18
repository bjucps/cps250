// strings
// A mashup of C string declaration and programming techniques
// (c) 2016, Bob Jones University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_char(char *cp) {
    *cp = 'X';
}

int main() {
    char foo;
    set_char(&foo);

    char __string_literal_1[] = {'h', 'i', '!', 0 };
    puts(__string_literal_1); // puts("hi!");

    puts("Answer is: " + 3);

    const char *cp = "foo";
    //cp[0] = 'F';
    puts(cp);

    int length;
    printf("How long of a string do you want? ");
    if (scanf("%d", &length) < 1) {
        perror("you didn't do the right thing!");
        exit(1);
    }
    char *string = malloc(length * sizeof(char));
    if (string == NULL) {
        perror("too much memories!");
    } else {
        snprintf(string, length, "Hello, world.  This string has room for %d characters!", length);
        puts(string);
        free(string);
    }

    return 0;
}

