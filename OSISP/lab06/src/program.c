#include "program.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INT_DIGIT 10

static void clearInputBuffer(void)
{
	int ch;

	while((ch = getchar()) != '\n' && ch != EOF) {}
}

void executeProg(char option, char* fileName, int memSize)
{
	int indexSize;
	char indexSizeStr[MAX_INT_DIGIT + 1];
	char* argv[] = {"prog", fileName, indexSizeStr, NULL};

	if(option == '1')
	{
		printf("\nВведите размер индексного файла в байтах.\n");
		printf("Требования: число больше %d, кратно 256 и %d.\n", memSize, memSize);
		printf("Размер файла: ");
		fflush(stdout);
		while(scanf("%d", &indexSize) != 1 || indexSize <= memSize || indexSize % memSize != 0)
		{
			printf("\nНекорректный ввод.\n");
			printf("Размер файла должен быть целым положительным числом,");
			printf(" больше %d и кратным %d.\n", memSize, memSize);
			printf("Повторите ввод: ");
			fflush(stdout);
			clearInputBuffer();
		}
		clearInputBuffer();

		snprintf(indexSizeStr, sizeof(indexSizeStr), "%d", indexSize);
	}
	else
	{
		argv[2] = NULL;
	}

	if(execve(option == '1' ? "./gen" : "./view", argv, NULL) == -1)
	{
		perror("Не удалось запустить дочернюю программу");
		exit(EXIT_FAILURE);
	}
}

void waitForProg(pid_t prog)
{
	if((waitpid(prog, NULL, 0)) == -1)
	{
		perror("Не удалось дождаться завершения дочернего процесса");
		exit(6);
	}
}
