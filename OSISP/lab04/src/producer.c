#define _XOPEN_SOURCE 500

#include "producer.h"
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

extern MessageQueue* queue;
static volatile sig_atomic_t stopProducer = 0;

static void producerSignalHandler(int signo)
{
    (void)signo;
    stopProducer = 1;
}

static void initProducerSignals(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = producerSignalHandler;
    sigemptyset(&action.sa_mask);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
}

void createProducer(Stack* producers, int* semId)
{
	fflush(stdout);
	pid_t producer = fork();
	switch (producer)
    {
        case 0:
            break;
        case -1:
            perror("fork");
            exit(errno);
        default:
			push(producers, producer);
            printf("Producer (PID=%d) created successfully. Current producers count: %d\n", producer, producers->size);
            return;
    }

    int addedCount;
    Message msg;
    srand((unsigned int)(time(NULL) ^ getpid()));
    initProducerSignals();

    while (!stopProducer)
    {
        produceMessage(&msg);
        if (semTryDown(semId, FREE_SLOTS_SEM) != 0)
        {
            usleep(100000);
            continue;
        }
        if (semTryDown(semId, MUTEX_SEM) != 0)
        {
            semUp(semId, FREE_SLOTS_SEM);
            usleep(100000);
            continue;
        }
        addedCount = putMessage(&msg);
        semUp(semId, MUTEX_SEM);
        if (addedCount >= 0)
        {
            semUp(semId, QUEUED_ITEMS_SEM);
        }
        else
        {
            semUp(semId, FREE_SLOTS_SEM);
        }

        if (addedCount >= 0)
        {
            printf("Pid: %d produce message: type = %02X | hash = %04X | size = %03d | addedCount = %d\n", getpid(), msg.type, msg.hash, msg.size, addedCount);
            fflush(stdout);
        }

        sleep(5);
    }
    _exit(0);
}

void deleteProducer(Stack* producers)
{
    pid_t pid = pop(producers);
    if (pid > 0)
    {
        kill(pid, SIGTERM);
        printf("Producer (PID=%d) removed successfully. Current producers count: %d\n", pid, producers->size);
        waitpid(pid, NULL, 0);
    }
}

void produceMessage(Message* msg)
{
    size_t alignedSize;

    memset(msg, 0, sizeof(Message));

    msg->type = (uint8_t)(rand() % 256);
    msg->size = (uint8_t)(rand() % 256);
    alignedSize = getAlignedDataLength(msg);

    for (size_t i = 0; i < alignedSize; ++i)
    {
        msg->data[i] = (uint8_t)(rand() % 256);
    }
    msg->hash = 0;
    msg->hash = calculateHash(msg);
}
