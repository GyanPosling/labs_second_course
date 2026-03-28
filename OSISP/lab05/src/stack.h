#pragma once

#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>

typedef struct
{
    pthread_t thread;
    atomic_bool stopRequested;
    unsigned int seed;
    int remainingMessages;
} ThreadControl;

typedef struct StackElem
{
    ThreadControl* control;
    struct StackElem* next;
} StackElem;

typedef struct
{
    StackElem* head;
    int size;
} Stack;

static inline uintptr_t threadToId(pthread_t thread)
{
    return (uintptr_t)thread;
}

Stack initStack(void);
ThreadControl* pushStack(Stack* stack);
ThreadControl* popStack(Stack* stack);
void destroyThreadControl(ThreadControl* control);
