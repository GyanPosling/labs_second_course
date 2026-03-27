#define _XOPEN_SOURCE 500

#include "consumer.h"
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern MessageQueue* queue;
static volatile sig_atomic_t stopConsumer = 0;

static void consumerSignalHandler(int signo)
{
    (void)signo;
    stopConsumer = 1;
}

static void initConsumerSignals(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = consumerSignalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
}

void createConsumer(Stack* consumers, int* semId)
{
	fflush(stdout);
	pid_t consumer = fork();
    switch (consumer)
    {
        case 0:
            break;
        case -1:
            perror("fork");
            exit(errno);
        default:
            push(consumers, consumer);
            printf("Consumer (PID=%d) created successfully. Current consumers count: %d\n", consumer, consumers->size);
            return;
    }

    Message msg;
    int extractedCount;
    initConsumerSignals();
    while (!stopConsumer)
    {
        if (semTryDown(semId, QUEUED_ITEMS_SEM) != 0)
        {
            usleep(100000);
            continue;
        }
        if (semTryDown(semId, MUTEX_SEM) != 0)
        {
            semUp(semId, QUEUED_ITEMS_SEM);
            usleep(100000);
            continue;
        }
        extractedCount = getMessage(&msg);
        semUp(semId, MUTEX_SEM);
        if (extractedCount >= 0)
        {
            semUp(semId, FREE_SLOTS_SEM);
        }
        else
        {
            semUp(semId, QUEUED_ITEMS_SEM);
        }
        if (extractedCount >= 0)
        {
            consumeMessage(&msg);
            printf("Pid: %d consume message: type = %02X | hash = %04X | size = %03d | extractedCount = %d\n", getpid(), msg.type, msg.hash, msg.size, extractedCount);
            fflush(stdout);
        }
        sleep(5);
    }
    _exit(0);
}

void deleteConsumer(Stack* consumers)
{
    pid_t pid = pop(consumers);
    if (pid > 0)
    {
        kill(pid, SIGTERM);
        printf("Consumer (PID=%d) removed successfully. Current consumers count: %d\n", pid, consumers->size);
        waitpid(pid, NULL, 0);
    }
}

void consumeMessage(Message *msg)
{
    uint16_t msgHash = msg->hash;
    msg->hash = 0;
    uint16_t checkSum = calculateHash(msg);
    if (msgHash != checkSum)
    {
        fprintf(stderr, "checkSum = %X not equal msgHash = %X\n", checkSum, msgHash);
    }
    msg->hash = msgHash;
}
