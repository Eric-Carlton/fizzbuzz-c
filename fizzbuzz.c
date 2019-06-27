#include <stdio.h> // printf, fprintf, scanf
#include <stdlib.h> // system, abort, strtol
#include <errno.h> // errno, ERANGE
#include <getopt.h> // getopt_long
#include <string.h> // strcpy, strlen
#include <stdbool.h> // true / false

#define MAX_STRING_ARG_LENGTH 20
#define MAX_END_NUMBER_DIGITS 10

struct FizzBuzzConfig {
	char fizz[MAX_STRING_ARG_LENGTH], buzz[MAX_STRING_ARG_LENGTH];
	bool valid;
};

void processOptions(int argc, char **argv, struct FizzBuzzConfig *config) {
	struct option longOpts[] =
	{
		{"fizz",  required_argument, 0, 'f'},
		{"buzz",    required_argument, 0, 'b'},
		{0, 0, 0, 0}
	};

	int opt;

	while (true) {
		opt = getopt_long (argc, argv, "f:b:", longOpts, NULL);

		// end of options, break out of loop
		if (opt == -1) break;

		switch (opt) {
		case 'f':
			if (strlen(optarg) > MAX_STRING_ARG_LENGTH) {
				fprintf(stderr, "Option -f has a max length of %d characters\n", MAX_STRING_ARG_LENGTH);
				config->valid = false;
			} else {
				strcpy(config->fizz, optarg);
			}
			break;
		case 'b':
			if (strlen(optarg) > MAX_STRING_ARG_LENGTH) {
				fprintf(stderr, "Option -b has a max length of %d characters\n", MAX_STRING_ARG_LENGTH);
				config->valid = false;
			} else {
				strcpy(config->buzz, optarg);
			}
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

int getStopNumberFromUser() {
	char unprocessedInput[MAX_END_NUMBER_DIGITS];

	printf("How high should I count? (must be greater than 0 and have fewer than %d digits; any whitespace constitutes end of input): ", MAX_END_NUMBER_DIGITS);
	// TODO: prevent inputs with greater length than MAX_END_NUMBER_DIGITS
	scanf("%s", unprocessedInput);

	int result = strtol(unprocessedInput, NULL, 10);

	if (errno == ERANGE) {
		printf("range error, got %d\n", result);
		return -1;
	}

	return result;
}

void playFizzbuzz(int start, int end, struct FizzBuzzConfig config) {
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

void handleInputError() {
	printf("Please enter a number greater than 0 with %d or fewer digits\n", MAX_END_NUMBER_DIGITS);
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
			handleInputError();
		}
	}
}