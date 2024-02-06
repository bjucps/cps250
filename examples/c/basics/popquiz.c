#include <stdio.h>

const char *suffixen[] = { "th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th" };

// Do integer division, returning both quotient (via normal return value)
// and remainder (via pointer-to-integer parameter)
int divmod(int numer, int denom, int *rem) {
    *rem = numer % denom;
    return numer / denom;
}

int main() {
    printf("Please enter your age: ");

    int age;
    if (scanf("%d", &age) < 1) {
        printf("\nERROR!  You didn't give me your age!\n");
        return 1;
	} else if (age < 1) {
		printf("\nERROR!  You are not allowed to be that young!\n");
		return 1;
    } else {
        printf("%d is a good age!\n", age);
    }
    
    int R;
    int Q = divmod(age, 10, &R);
	Q += 1;
    printf("You are %d years into your %d%s decade!\n", R, Q, suffixen[Q % 10]);

    return 0;
}
