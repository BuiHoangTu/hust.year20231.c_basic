#include "list/stack.h"


Stack* stack_create() {
    return sll_create();
}

void stack_push(Stack* stack, void* value) {
    sll_insert(stack, value, 0);
}

void* stack_pop(Stack* stack) {
    return sll_remove(stack, 0);
}

void* stack_peek(Stack* stack) {
    return sll_get(stack, 0);
}

void stack_free(Stack* stack) {
    sll_free(stack);
}