#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <locale.h>

#define MAX_VAL_LEN 128
#define MAX_KEY_LEN 128
#define DEFAULT_ENV_FILE "env.txt"

extern char **environ;

void printStrings(char **env, int size);

int compStrings(const void* string1, const void* string2);

void getEnvp(char ***env, int *size, char* envp[]);

char **getChildEnv(const char *envFilePath, int *size);

void executeChild(char option, int childCount, char** childEnvVariables);

void waitForChild(pid_t child);

void freeEnv(char **env, int size);

const char *getEnvFilePath(void);
