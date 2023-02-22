#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int guess(char *prompt, int value) {
	printf("%s: ", prompt);
	char *buff = malloc(50);			// oof, malloc for a local/temp??
	fgets(buff, sizeof buff, stdin);  	// ooof, sizeof(<pointer>)???
	int guess = atoi(buff);
	if (guess < value) {
		printf("too low!\n");
		return -1;						// oooof, leak buff????
	} else if (guess > value) {
		printf("too high!\n");
		return 1;						// ooooof...
	} else {
		printf("you win!\n");
		return 0;						// OOOOOOF.......................
	}
}


int main(int argc, char **argv) {
	srand(time(NULL));
	int goal = rand() % 100;  // biased random number in range [0,99]
	printf("I'm thinking of a number between 0 and 99...\n");
	while (guess("guess", goal));
}
