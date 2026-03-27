#pragma once

#include "queue.h"
#include "stack.h"

void createProducer(Stack* producers, int* semId);
void deleteProducer(Stack* producers);

void produceMessage(Message *msg);
