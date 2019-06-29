#include <stdio.h> // printf, fprintf
#include <stdlib.h> // system, abort, strtol
#include <errno.h> // errno
#include <getopt.h> // getopt_long
#include <string.h> // strcpy, strlen
#include <stdbool.h> // true / false

struct FizzBuzzConfig {
	char *fizz, *buzz;
	bool valid;
};

void processOptions(int argc, char **argv, struct FizzBuzzConfig *config) {
	struct option longOpts[] =
	{
		{"fizz", required_argument, 0, 'f'},
		{"buzz", required_argument, 0, 'b'},
		{0, 0, 0, 0}
	};

	while (true) {
		int opt = getopt_long (argc, argv, "f:b:", longOpts, NULL);

		// end of options, break out of loop
		if (opt == -1) break;

		switch (opt) {
		case 'f':
			config->fizz = optarg;
			break;
		case 'b':
			config->buzz = optarg;
			break;
		case '?':
			if (optopt == 'f' || optopt == 'b') {
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				config->valid = false;
			}
			break;
		default:
			abort();
		}
	}
}

void printIntro(struct FizzBuzzConfig config) {
	system("clear");

	printf("I will say '%s' for every number divisible by 3\n", config.fizz);
	printf("I will say '%s' for every number divisible by 5\n", config.buzz);
	printf("I will start at counting at 1, and end with a number that you specify\n");
	printf("\n");
}

unsigned int getStopNumberFromUser() {
	printf("How high should I count? (must be greater than 0; any whitespace constitutes end of input): ");

	unsigned int maxLength = 4;
	unsigned int currentLength, i = 0;
	char *unprocessedInput = malloc(maxLength);
	int userInputChar = EOF;

	while (( userInputChar = getchar() ) != '\n' && userInputChar != EOF) {
		unprocessedInput[i++]=(char)userInputChar;

		// we've reached the max input size, need to allocate more memory
		if(i == currentLength) {
            currentLength = i+maxLength;
			unprocessedInput = realloc(unprocessedInput, currentLength);
		}
	}
	
	unprocessedInput[i] = '\0';
    
	unsigned int result = strtol(unprocessedInput, NULL, 10);

	// allocated with alloc, so we need to manually free
	free(unprocessedInput);
	unprocessedInput = NULL;

	return result;
}

void playFizzbuzz(int start, unsigned int end, struct FizzBuzzConfig config) {
	for (int i = start; i <= end; i++) {
		printf("%d: ", i);
		if (i % 3 == 0) {
			printf("%s", config.fizz);
		}
		if (i % 5 == 0) {
			printf("%s", config.buzz);
		}
		printf("\n");
	}
}

int main(int argc, char **argv) {
	// this is the default config, will be overwritten with
	// the values of any options passed
	struct FizzBuzzConfig config = {"FIZZ", "BUZZ", true};
	processOptions(argc, argv, &config);

	if (config.valid) {
		printIntro(config);

		int end = getStopNumberFromUser();

		if (end > 0) {
			playFizzbuzz(1, end, config);
		} else {
			printf("Please enter a number greater than 0\n");
		}
	}
}