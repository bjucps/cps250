// pointerparam
// A simple demonstration of using pointer parameters to effect pass-by-reference semantics
// (c) 2016, Bob Jones University
#include <stdio.h>

// Do integer division, returning both quotient (via normal return value)
// and remainder (via pointer-to-integer parameter)
int divmod(int numer, int denom, int *rem) {
    *rem = numer % denom;
    return numer / denom;
}

int main() {
    int R;
    int Q = divmod(42, 10, &R);

    printf("42 / 10 = %dr%d\n", Q, R);

    return 0;
}


