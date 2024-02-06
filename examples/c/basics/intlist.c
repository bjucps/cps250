#include <stdio.h>
#include <assert.h>

int sum_int_list(int *array, size_t arrlen) {
    int sum = 0;
    for (int i = 0; i < arrlen; ++i) {
        sum += array[i];
    }
    return sum;
}

void init_int_list(int *array, size_t arrlen, int init_value) {
    for (int i = 0; i < arrlen; ++i) {
        array[i] = init_value;
    }
}

void append_int_list(int *array, size_t *arrused, size_t arrsize, int new_value) {
    assert(*arrused < arrsize);  // blow up if we're out of room
    array[*arrused] = new_value;
    *arrused += 1;
}

int main() {
    int arr[10];
    size_t arrsize = sizeof(arr) / sizeof(int);

	init_int_list(arr, arrsize, 0);
    size_t arrused = 0;

    append_int_list(arr, &arrused, arrsize, 1);
    append_int_list(arr, &arrused, arrsize, 2);
    append_int_list(arr, &arrused, arrsize, 3);
    append_int_list(arr, &arrused, arrsize, 42);

	printf("1 + 2 + 3 + 42 == %d\n", sum_int_list(arr, arrused));

	return 0;
}
