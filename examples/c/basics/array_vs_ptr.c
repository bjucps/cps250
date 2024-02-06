#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;

    printf("sizeof arr == %zu\n", sizeof arr);
    printf("sizeof ptr == %zu\n", sizeof ptr);
    printf("sizeof(int) == %zu\n", sizeof(int));

    printf("arr[0] == %d\n", arr[0]);   // logical!
    printf("&arr[0] == %p\n", &arr[0]);
    printf("*ptr == %d\n", *ptr);       // also logical!
    printf("&*ptr == ptr == %p\n", ptr);

    printf("arr[1] == %d @ %p\n", arr[1], &arr[1]);             // ok...
    printf("*(ptr + 1) == %d @ %p\n", *(ptr + 1), ptr + 1);     // right...
    printf("*(2 + ptr) == %d @ %p\n", *(2 + ptr), 2 + ptr);     // commutitive!
    printf("2[arr] == %d @ %p\n", 2[arr], &(2[arr]));           // wait...WAT?!

    return 0;
}
