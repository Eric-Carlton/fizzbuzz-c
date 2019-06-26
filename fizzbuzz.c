#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 20

struct FizzBuzzConfig {
	char fizz[MAX_INPUT_LENGTH], buzz[MAX_INPUT_LENGTH];
	bool valid;
};

void processOptions(int argc, char **argv, struct FizzBuzzConfig *config) {
	int opt;

	while ((opt = getopt(argc, argv, "f:b:")) != -1) {
	    switch (opt)
	      {
		      case 'f':
		      	if(strlen(optarg) > MAX_INPUT_LENGTH) {
		      		fprintf(stderr, "Option -f has a max length of %d characters\n", MAX_INPUT_LENGTH);
		      		config->valid = false;
		      	} else {
		      		strcpy(config->fizz, optarg);
		      	}
		        break;
		      case 'b':
		        if(strlen(optarg) > MAX_INPUT_LENGTH) {
		      		fprintf(stderr, "Option -b has a max length of %d characters\n", MAX_INPUT_LENGTH);
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
	char unprocessedInput[10];

	printf("How high should I count? (must be greater than 0 and have fewer than %d digits; any whitespace constitutes end of input): ", MAX_INPUT_LENGTH);
    scanf("%s", unprocessedInput);

    int result = strtol(unprocessedInput, NULL, MAX_INPUT_LENGTH);

    if(errno == ERANGE) {
    	printf("range error, got %d\n", result);
    	return -1;
    }

    return result;
}

void playFizzbuzz(int start, int end, struct FizzBuzzConfig config) {
	for(int i = start; i <= end; i++) {
		printf("%d: ", i);
		if(i % 3 == 0) {
			printf("%s", config.fizz);
		}
		if(i % 5 == 0) {
			printf("%s", config.buzz);
		}
		printf("\n");
	}
}

void handleInputError() {
	printf("Please enter a number greater than 0 with 10 or fewer digits\n");
}

int main(int argc, char **argv) {
	// this is the default config, will be overwritten with
	// the values of any options passed
	struct FizzBuzzConfig config = {"FIZZ", "BUZZ", true};
	processOptions(argc, argv, &config);

	if(config.valid) {
		printIntro(config);

		int end = getStopNumberFromUser();

		if(end > 0) {
			playFizzbuzz(1, end, config);
		} else {
			handleInputError();
		}
	}
}