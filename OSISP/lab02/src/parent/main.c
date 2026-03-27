#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "environment.h"

int main(int argc, char* argv[], char* envp[]) {
	char **parentEnv = NULL;
	char **childEnv = NULL;
	int parentEnvSize = 0;
	int childEnvSize = 0;
	pid_t child;
	char option;
	unsigned childCount = 0;
	const char *envFilePath;

	(void)argc;
	(void)argv;

	setenv("LC_COLLATE", "C", 1);
	if(setlocale(LC_COLLATE, "C") == NULL) {
		fprintf(stderr, "Can't set LC_COLLATE to C. Program stopped.\n");
		return 1;
	}

	getEnvp(&parentEnv, &parentEnvSize, envp);
	qsort(parentEnv, parentEnvSize, sizeof(char*), compStrings);
	printf("Parent environment variables (%d):\n", parentEnvSize);
	printf("---------------------------------------------\n");
	printStrings(parentEnv, parentEnvSize);

	envFilePath = getEnvFilePath();
	childEnv = getChildEnv(envFilePath, &childEnvSize);

	do {
		printf("\n------------------ MENU ---------------------\n");
		printf("  +   Show env in child via environ\n");
		printf("  *   Show env in child via envp[] (main arg)\n");
		printf("  q   Quit\n");
		printf("---------------------------------------------\n");
		printf("Select option (+, *, q): ");

		option = getchar();
		while ((getchar()) != '\n');

		switch (option) {
			case '+':
			case '*':
				child = fork();
				if(child < 0) {
					fprintf(stderr, "Can't create child process. Program stopped.");
					exit(7);
				}
				else {
					if(child == 0) {
						executeChild(option, childCount, childEnv);
					}
					else {
						++childCount;
					}
				}
				break;
			case 'q':
				break;
			default:
				fprintf(stderr, "Wrong input. Print \"+\", \"*\" or \"q\"\n");
				break;
		}
	} while(option != 'q');

	freeEnv(parentEnv, parentEnvSize);
	freeEnv(childEnv, childEnvSize);
	return 0;
}
