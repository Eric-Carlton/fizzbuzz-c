#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void printIntro() {
	system("clear");

	printf("I will say 'FIZZ' for every number divisible by 3\n");
	printf("I will say 'BUZZ' for every number divisible by 5\n");
	printf("I will start at counting at 1, and end with a number that you specify\n");
	printf("\n");
}

int getUserInput() {
	char unprocessedInput[10];

	printf("How high should I count? (must be greater than 0 and have fewer than 10 digits; any whitespace constitutes end of input): ");
    scanf("%s", unprocessedInput);

    int result = strtol(unprocessedInput, NULL, 10);

    if(errno == ERANGE) {
    	printf("range error, got %d\n", result);
    	return -1;
    }

    return result;
}

void playFizzbuzz(int start, int end) {
	for(int i = start; i <= end; i++) {
		printf("%d: ", i);
		if(i % 3 == 0) {
			printf("FIZZ");
		}
		if(i % 5 == 0) {
			printf("BUZZ");
		}
		printf("\n");
	}
}

void handleInputError() {
	printf("Please enter a number greater than 0 with 10 or fewer digits\n");
}

int main() {
	printIntro();

	int end = getUserInput();

	if(end > 0) {
		playFizzbuzz(1, end);
	} else {
		handleInputError();
	}
}