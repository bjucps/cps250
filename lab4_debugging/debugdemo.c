#include <stdio.h>
#include <bsd/string.h>

int count = 0;

double sumnums(double *nums, size_t numnums) {
    double sum = 0;
    for (int i = 0; i < numnums; ++i) {
        sum += nums[i];
    }
    return sum;
}

int main(int argc, char **argv) {
    double nums[] = { 5.1, 6.3, 3.5 };
    double result = 0;

    puts("Preparing to sum nums...");
    result = sumnums(nums, sizeof(nums) / sizeof(nums[0]));
    printf("Sum = %lf\n", result);

    return 0;
}

