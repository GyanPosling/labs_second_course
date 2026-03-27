#define _POSIX_C_SOURCE 200809L
#include "environment.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

void printStrings(char **env, int size) {
	for(int i = 0; i < size; ++i) {
		printf("%s\n", env[i]);
	}
}

int compStrings(const void* string1, const void* string2) {
	return strcoll(*(const char **)string1, *(const char **)string2);
}

void getEnvp(char ***env, int *size, char* envp[]) {
	int count = 0;
	while(envp[count] != NULL) count++;

	*env = (char**)malloc((count + 1) * sizeof(char*));
	if(*env == NULL) {
		fprintf(stderr, "Can't allocate memory. Program stopped\n");
		exit(2);
	}

	for(int i = 0; i < count; ++i) {
		(*env)[i] = strdup(envp[i]);
		if((*env)[i] == NULL) {
			fprintf(stderr, "Can't allocate memory. Program stopped\n");
			exit(3);
		}
	}

	(*env)[count] = NULL;
	*size = count;
}

const char *getEnvFilePath(void) {
	const char *envPath = getenv("ENV_PATH");

	if(envPath != NULL && envPath[0] != '\0') {
		return envPath;
	}

	return DEFAULT_ENV_FILE;
}

char **getChildEnv(const char *envFilePath, int *size) {
	FILE* file = fopen(envFilePath, "r");
	char envVar[MAX_VAL_LEN + MAX_KEY_LEN + 1];
	char envKey[MAX_KEY_LEN];
	char* envVal;
	char **childEnv = NULL;
	int capacity = 16;
	int count = 0;
	char* end;

	if(file == NULL) {
		fprintf(stderr, "Can't open env file \"%s\". Program stopped.\n", envFilePath);
		exit(5);
	}

	childEnv = (char**)malloc((capacity + 1) * sizeof(char*));
	if(childEnv == NULL) {
		fprintf(stderr, "Can't allocate memory. Program stopped\n");
		exit(2);
	}

	while((fgets(envKey, MAX_KEY_LEN, file)) != NULL) {
		end = strstr(envKey, "\n");
		if (end != NULL) {
			*end = '\0';
		}

		envVal = getenv(envKey);
		if(envVal != NULL) {
			if(count == capacity) {
				capacity *= 2;
				childEnv = realloc(childEnv, (capacity + 1) * sizeof(char*));
				if(childEnv == NULL) {
					fprintf(stderr, "Can't allocate memory. Program stopped\n");
					exit(2);
				}
			}

			snprintf(envVar, sizeof(envVar), "%s=%s", envKey, envVal);
			childEnv[count] = strdup(envVar);
			if(childEnv[count] == NULL) {
				fprintf(stderr, "Can't allocate memory. Program stopped\n");
				exit(3);
			}
			count++;
		}
		else {
			printf("Can't find value of %s. Key skipped.\n", envKey);
		}
	}
	fclose(file);

	childEnv[count] = NULL;
	*size = count;
	return childEnv;
}

void executeChild(char option, int childCount, char** childEnvVariables) {
	char childName[9];
	char childPath[PATH_MAX];
	const char *childDir = getenv("CHILD_PATH");
	char optionArg[2];
	char* argv[] = {childName, optionArg, NULL};

	snprintf(childName, sizeof(childName), "child_%02u", childCount % 100);
	optionArg[0] = option;
	optionArg[1] = '\0';

	if(childDir == NULL || childDir[0] == '\0') {
		snprintf(childPath, sizeof(childPath), "./child");
	}
	else {
		snprintf(childPath, sizeof(childPath), "%s/child", childDir);
	}

	if(execve(childPath, argv, childEnvVariables) == -1) {
		fprintf(stderr, "Can't execute child program \"%s\". Program stopped.\n", childPath);
		exit(1);
	}
}

void waitForChild(pid_t child) {
	int status;

	if(waitpid(child, &status, 0) == -1) {
		fprintf(stderr, "Can't wait for child process. Program stopped.\n");
		exit(6);
	}
}

void freeEnv(char **env, int size) {
	if(env != NULL) {
		for(int i = 0; i < size; ++i) {
			free(env[i]);
		}
		free(env);
	}
}
