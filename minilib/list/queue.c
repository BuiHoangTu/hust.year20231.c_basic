#include "list/queue.h"


Queue* queue_create() {
    return sll_create();
}

void enqueue(Queue* queue, void* value) {
    sll_add_last(queue, value);
}

void* dequeue(Queue* queue) {
    return sll_remove(queue, 0);
}

void* queue_peek(Queue* queue) {
    return sll_get(queue, 0);
}

void queue_free(Queue* queue) {
    sll_free(queue);
}