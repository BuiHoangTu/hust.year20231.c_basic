#ifndef QUEUE_H_
#define QUEUE_H_

#include "list/single_linked_list.h"

#define Queue SingleLinkedList

Queue* queue_create();

void enqueue(Queue* queue, void* value);

void* dequeue(Queue* queue);

void* queue_peek(Queue* queue);

void queue_free(Queue* queue);


#endif // QUEUE_H_