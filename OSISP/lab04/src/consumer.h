#pragma once

#include "queue.h"
#include "stack.h"

void createConsumer(Stack* consumers, int* semId);
void deleteConsumer(Stack* consumers);

void consumeMessage(Message *msg);
