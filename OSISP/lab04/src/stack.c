#define _XOPEN_SOURCE 500

#include "stack.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

Stack initStack(void)
{
	Stack stack;

	stack.head = NULL;
	stack.size = 0;

	return stack;
}

void push(Stack* stack, pid_t child)
{
	struct StackElem* elem = (struct StackElem*)malloc(sizeof(struct StackElem));
	if(elem == NULL)
	{
		perror("Can't allocate memory");
		exit(1);
	}

	elem->value = child;
	elem->next = stack->head;
	stack->head = elem;
	++stack->size;
}

pid_t pop(Stack* stack)
{
	if(stack->size == 0)
	{
		printf("\nStack is empty\n\n");
		return 0;
	}

	struct StackElem* temp = stack->head;
	pid_t value = temp->value;
	stack->head = stack->head->next;
	temp->next = NULL;
	free(temp);

	--stack->size;

	return value;
}

void clear(Stack* stack)
{
	while (stack->size != 0)
	{
		pid_t pid = pop(stack);
		if (pid > 0)
		{
			kill(pid, SIGTERM);
			waitpid(pid, NULL, 0);
		}
	}
}
