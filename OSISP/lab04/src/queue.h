#pragma once

#include <stddef.h>
#include <stdint.h>

#define MAX_DATA (((256 + 3) / 4) * 4)
#define MAX_MESSAGES 10

#define MUTEX_SEM 0
#define FREE_SLOTS_SEM 1
#define QUEUED_ITEMS_SEM 2

typedef struct __attribute__((packed))
{
    uint8_t type;
    uint16_t hash;
    uint8_t size;
    uint8_t data[MAX_DATA];
} Message;

_Static_assert(offsetof(Message, type) == 0, "Message.type must be at offset 0");
_Static_assert(offsetof(Message, hash) == 1, "Message.hash must be at offset 1");
_Static_assert(offsetof(Message, size) == 3, "Message.size must be at offset 3");
_Static_assert(offsetof(Message, data) == 4, "Message.data must be at offset 4");

typedef struct
{
    int addedCount;
    int extractedCount;
    int messageCount;
    int freeCount;
    int head;
    int tail;
    int freeTop;
    Message* buffer[MAX_MESSAGES];
    Message storage[MAX_MESSAGES];
    int freeIndexes[MAX_MESSAGES];
} MessageQueue;

size_t getMessageDataLength(const Message* msg);
size_t getAlignedDataLength(const Message* msg);
uint16_t calculateHash(const Message* msg);
MessageQueue initQueue(void);

int putMessage(Message* msg);
int getMessage(Message* msg);

void semDown(int* semId, int semNum);
int semTryDown(int* semId, int semNum);
void semUp(int* semId, int semNum);
