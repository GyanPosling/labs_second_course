#pragma once

#include <sys/types.h>

struct StackElem
{
	pid_t value;
	struct StackElem* next;
};

typedef struct
{
	struct StackElem* head;
	int size;
} Stack;

Stack initStack(void);
void push(Stack* stack, pid_t child);
pid_t pop(Stack* stack);
void clear(Stack* stack);
