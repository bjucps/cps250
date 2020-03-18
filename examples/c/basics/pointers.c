// pointers
// A simple demonstration of objects, object addresses, and pointer variables
// (c) 2016, Bob Jones University
#include <stdio.h>

int main() {
    int x = 42;
    printf("Variable x lives at address %p and contains the integer %d\n", &x, x);

    int *ptr_to_x = &x;
    printf("Variable px lives at address %p and contains the pointer value %p\n", &ptr_to_x, ptr_to_x);
    printf("The object px points to currently contains the integer %d\n", *ptr_to_x);

    *ptr_to_x = 1337;   // Changes x _via_ ptr_to_x
    printf("Variable x now contains the integer %d\n", x);
}

