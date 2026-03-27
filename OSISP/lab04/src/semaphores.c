#define _XOPEN_SOURCE 500

#include "semaphores.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

extern MessageQueue* queue;

void initSemaphores(int* semId)
{
	int shmid = shmget(SHM_KEY, sizeof(MessageQueue), SHM_FLAGS);
    if (shmid == -1)
    {
        perror("shmget");
        exit(errno);
    }

    queue = (MessageQueue*)shmat(shmid, NULL, 0);
    if (queue == (void*)-1)
    {
        perror("shmat");
        exit(errno);
    }
    *queue = initQueue();

    *semId = semget(SEM_KEY, 3, SEM_FLAGS);
    if (*semId == -1)
    {
        perror("semget");
        exit(errno);
    }

    union semun arg;

    arg.val = 1;
    if (semctl(*semId, MUTEX_SEM, SETVAL, arg) == -1)
    {
        perror("semctl mutex");
        exit(errno);
    }


    arg.val = MAX_MESSAGES;
    if (semctl(*semId, FREE_SLOTS_SEM, SETVAL, arg) == -1)
    {
        perror("semctl free_space");
        exit(errno);
    }


    arg.val = 0;
    if (semctl(*semId, QUEUED_ITEMS_SEM, SETVAL, arg) == -1)
    {
        perror("semctl items");
        exit(errno);
    }
}

void deleteSemaphores(Stack* producers, Stack* consumers, int* semId)
{
	while (producers->size != 0)
	{
		pid_t pid = pop(producers);
		if (pid > 0)
		{
			kill(pid, SIGTERM);
			waitpid(pid, NULL, 0);
		}
	}
	while (consumers->size != 0)
	{
		pid_t pid = pop(consumers);
		if (pid > 0)
		{
			kill(pid, SIGTERM);
			waitpid(pid, NULL, 0);
		}
	}

	int shmid = shmget(SHM_KEY, 0, 0);
	if (queue != NULL && queue != (void*)-1)
	{
        shmdt(queue);
        queue = NULL;
    }

	if (shmid != -1)
	{
		shmctl(shmid, IPC_RMID, NULL);
	}
	if (*semId != -1)
	{
		semctl(*semId, 0, IPC_RMID);
		*semId = -1;
	}
}
