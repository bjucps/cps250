// pointermath
// A small demonstration of the joys of pointer arithmetic
// (c) 2016, Bob Jones University
#include <stdio.h>

int main() {
    int array[5] = { 1, 2, 3, 4, 5 };

    // Printing addresses taken using array syntax
    printf("array is located at address %p\n", &array[0]);
    printf("array[3] is located at address %p\n", &array[3]);

    // Printing the same addresses taken using pointer arithmetic syntax
    int *ptr = array;
    printf("ptr == %p\nptr + 3 == %p\n", ptr, ptr + 3);

    // Dereferencing using * and using []
    printf("*ptr == array[0] -> %d\n", (*ptr == array[0]));

    return 0;
}

