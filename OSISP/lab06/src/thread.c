#include "thread.h"
#include "thread.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ThreadInfo* initThreadInfo(int threadCount, int blockSize, int blocksCount, int indexesInBlock)
{
	ThreadInfo* info = (ThreadInfo*)calloc(threadCount, sizeof(ThreadInfo));
	if(info == NULL)
	{
		perror("Не удалось выделить память");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < threadCount; ++i)
	{
		info[i].blockSize = blockSize;
		info[i].blocksCount = blocksCount;
		info[i].indexesInBlock = indexesInBlock;
		info[i].id = i;
	}

	return info;
}

pthread_t* initThreads(int threadCount)
{
	pthread_t* threads = (pthread_t*)malloc(threadCount * sizeof(pthread_t));
	if(threads == NULL)
	{
		perror("Не удалось выделить память");
		exit(EXIT_FAILURE);
	}

	return threads;
}

void joinThreads(pthread_t* threads, int threadCount)
{
	for(int i = 1; i < threadCount; ++ i)
	{
		int error = pthread_join(threads[i], NULL);
		if(error != 0)
		{
			fprintf(stderr, "Не удалось дождаться завершения потока: %s\n", strerror(error));
			exit(EXIT_FAILURE);
		}
	}
}
