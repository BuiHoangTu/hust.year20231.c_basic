#ifndef QUEUE_H_
#define QUEUE_H_

#include "list/single_linked_list.h"

#define Queue SingleLinkedList

Queue* createQueue();

void enqueue(Queue* queue, void* value);

void* dequeue(Queue* queue);

void* queuePeek(Queue* queue);

void queueFree(Queue* queue);


#endif // QUEUE_H_