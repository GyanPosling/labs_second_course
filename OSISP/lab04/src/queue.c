#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>


extern MessageQueue* queue;

size_t getMessageDataLength(const Message* msg)
{
    return (size_t)msg->size + 1U;
}

size_t getAlignedDataLength(const Message* msg)
{
    size_t dataLength = getMessageDataLength(msg);
    return ((dataLength + 3U) / 4U) * 4U;
}

uint16_t calculateHash(const Message* msg)
{
    Message normalized = *msg;
    const uint8_t* bytes = (const uint8_t*)&normalized;
    uint16_t hash = 0;
    size_t meaningfulLength = offsetof(Message, data) + getMessageDataLength(&normalized);

    normalized.hash = 0;



    for (size_t i = 0; i < meaningfulLength; ++i) {
        hash = (hash * 33) ^ bytes[i];
    }
    return hash;
}

MessageQueue initQueue(void)
{
	MessageQueue queue;

    queue.addedCount = 0;
    queue.extractedCount = 0;
    queue.messageCount = 0;
    queue.freeCount = MAX_MESSAGES;
    queue.head = 0;
    queue.tail = 0;
    queue.freeTop = MAX_MESSAGES;
    for (int i = 0; i < MAX_MESSAGES; ++i)
    {
        queue.buffer[i] = NULL;
        queue.freeIndexes[i] = MAX_MESSAGES - i - 1;
    }
    memset(queue.storage, 0, sizeof(queue.storage));
    memset(queue.buffer, 0, sizeof(queue.buffer));
    return queue;
}

int putMessage(Message* msg)
{
    if (queue->freeTop == 0)
    {
        return -1;
    }

    int freeIndex = queue->freeIndexes[queue->freeTop - 1];
    --queue->freeTop;
    queue->storage[freeIndex] = *msg;

    if (queue->head == MAX_MESSAGES)
    {
        queue->head = 0;
    }
    queue->buffer[queue->head] = &queue->storage[freeIndex];
    ++queue->head;
    ++queue->messageCount;
    --queue->freeCount;
    ++queue->addedCount;
    return queue->addedCount;
}

int getMessage(Message* msg)
{
    if (queue->tail == MAX_MESSAGES)
    {
        queue->tail = 0;
    }

    Message* queuedMessage = queue->buffer[queue->tail];
    if (queuedMessage == NULL)
    {
        return -1;
    }

    *msg = *queuedMessage;
    queue->buffer[queue->tail] = NULL;

    int freeIndex = (int)(queuedMessage - queue->storage);
    if (queue->freeTop < MAX_MESSAGES)
    {
        queue->freeIndexes[queue->freeTop] = freeIndex;
        ++queue->freeTop;
    }

    ++queue->tail;
    --queue->messageCount;
    ++queue->freeCount;
    ++queue->extractedCount;

    return queue->extractedCount;
}

void semDown(int* semId, int semNum)
{
    struct sembuf op = {semNum, -1, 0};
    if (semop(*semId, &op, 1))
    {
        perror("semop down");
        exit(EXIT_FAILURE);
    }
}

int semTryDown(int* semId, int semNum)
{
    struct sembuf op = {semNum, -1, IPC_NOWAIT};
    if (semop(*semId, &op, 1) == 0)
    {
        return 0;
    }
    if (errno == EAGAIN || errno == EINTR)
    {
        return 1;
    }

    perror("semop try down");
    exit(EXIT_FAILURE);
}

void semUp(int* semId, int semNum)
{
    struct sembuf op = {semNum, 1, 0};
    if (semop(*semId, &op, 1))
    {
        perror("semop up");
        exit(EXIT_FAILURE);
    }
}
