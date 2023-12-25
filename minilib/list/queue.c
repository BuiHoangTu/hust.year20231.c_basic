#include "list/queue.h"


Queue* createQueue() {
    return CreateSll();
}

void enqueue(Queue* queue, void* value) {
    sllAddLast(queue, value);
}

void* dequeue(Queue* queue) {
    return sllRemove(queue, 0);
}

void* queuePeek(Queue* queue) {
    return sllGet(queue, 0);
}

void queueFree(Queue* queue) {
    sllFree(queue);
}