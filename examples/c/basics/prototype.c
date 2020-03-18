// prototype
// A demonstration of function prototypes (in a situation involving mutual recursion,
// where at least one function must be forward-declared to avoid warnings).
// (c) 2016, Bob Jones University
#include <stdio.h>

void pong(int );

void ping(int rep) {
    printf("ping(%d)\n", rep);
    if (rep > 0) pong(rep - 1);
}

void pong(int rep) {
    printf("pong(%d)\n", rep);
    if (rep > 0) ping(rep - 1);
}

int main() {
    ping(3);
    return 0;
}
