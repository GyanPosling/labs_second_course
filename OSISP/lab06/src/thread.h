#pragma once
#include "index.h"
#include <pthread.h>

typedef struct
{
	Index* address;
	int blockSize;
	int blocksCount;
	int indexesInBlock;
	int id;
} ThreadInfo;

ThreadInfo* initThreadInfo(int threadCount, int blockSize, int blockCount, int indexesInBlock);
pthread_t* initThreads(int threadCount);

void joinThreads(pthread_t* threads, int threadCount);
