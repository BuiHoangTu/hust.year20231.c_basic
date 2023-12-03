//
// Created by bhtuw on 20/11/2023.
//
#include "list/stack.h"
#include "core/heap.h"
#include <stdio.h>

int main() {
    int i;
    Stack *stack = stack_create();
    SingleLinkedList *list = sll_create();
    void* pop;

    i = 10;
    stack_push(stack, copy2heap(&i, sizeof(int)));

    pop = stack_pop(stack);
    sll_add_last(list, pop);

    i = 11;
    stack_push(stack, copy2heap(&i, sizeof(int)));

    i = 1;
    stack_push(stack, copy2heap(&i, sizeof(int)));

    i = 3;
    stack_push(stack, copy2heap(&i, sizeof(int)));

    // 11
    pop = stack_pop(stack);
    sll_add_last(list, pop);

    i = 5;
    stack_push(stack, copy2heap(&i, sizeof(int)));

    i = 4;
    stack_push(stack, copy2heap(&i, sizeof(int)));

    // 5
    pop = stack_pop(stack);
    sll_add_last(list, pop);


    printf("\nPrint all\n");
    sll_foreach(o, list) {
        printf("%d", void2(int, o));
    }

}