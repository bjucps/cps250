// passarray
// A demonstration of how arrays are [not, in fact] passed to functions in C.
// (c) 2016, Bob Jones University
#include <stdio.h>

void take_array(int array[10]) {
    printf("take_array() received an array that starts at %p and is %zu bytes long\n", &array[0], sizeof(array));
}

int main() {
    int nums[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 42 };

    printf("main() passes an array that starts at %p and is %zu bytes long\n", &nums[0], sizeof(nums));
    take_array(nums);

    return 0;
}

