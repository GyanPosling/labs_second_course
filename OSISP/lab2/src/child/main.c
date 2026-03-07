#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "environment.h"

int main(int argc, char* argv[], char* envp[]) {
	char **childEnv = NULL;    
	int childEnvSize = 0;      

	(void)argc;

	if(setlocale(LC_COLLATE, "C") == NULL) {
		fprintf(stderr, "Can't set LC_COLLATE to C. Program stopped.\n");
		return 1;
	}

	printf("\n====================================================\n");
	printf("  Child Environment Viewer\n");
	printf("====================================================\n");
	printf("Program : %s\n", argv[0]);
	printf("PID     : %d\n", getpid());
	printf("PPID    : %d\n", getppid());
	printf("----------------------------------------------------\n");

	if(argc > 1 && strcmp(argv[1], "+") == 0) {
		getEnvp(&childEnv, &childEnvSize, environ);
		printf("Child process environment via environ:\n");
	}
	else if(argc > 1 && strcmp(argv[1], "*") == 0) {
		getEnvp(&childEnv, &childEnvSize, envp);
		printf("Child process environment via *envp[]:\n");
	}
	else {
		fprintf(stderr, "Wrong child startup option.\n");
		return 1;
	}

	qsort(childEnv, childEnvSize, sizeof(char*), compStrings);
	printStrings(childEnv, childEnvSize);		

	freeEnv(childEnv, childEnvSize);		

	return 0;
}
