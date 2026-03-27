#pragma once

#include <sys/ipc.h>

#include "queue.h"
#include "stack.h"

#define SHM_KEY 0x1234
#define SEM_KEY 0x5678
#define SHM_FLAGS (IPC_CREAT | 0600)
#define SEM_FLAGS (IPC_CREAT | 0600)

void initSemaphores(int* semId);
void deleteSemaphores(Stack* producers, Stack* consumers, int* semId);
