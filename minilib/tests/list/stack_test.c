//
// Created by bhtuw on 20/11/2023.
//
#include "list/stack.h"
#include "core/heap.h"
#include <stdio.h>

int main() {
    int i;
    Stack *stack = createStack();
    SingleLinkedList *list = CreateSll();
    void* pop;

    i = 10;
    stackPush(stack, copy2heap(&i, sizeof(int)));

    pop = stackPop(stack);
    sllAddLast(list, pop);

    i = 11;
    stackPush(stack, copy2heap(&i, sizeof(int)));

    i = 1;
    stackPush(stack, copy2heap(&i, sizeof(int)));

    i = 3;
    stackPush(stack, copy2heap(&i, sizeof(int)));

    // 11
    pop = stackPop(stack);
    sllAddLast(list, pop);

    i = 5;
    stackPush(stack, copy2heap(&i, sizeof(int)));

    i = 4;
    stackPush(stack, copy2heap(&i, sizeof(int)));

    // 5
    pop = stackPop(stack);
    sllAddLast(list, pop);


    printf("\nPrint all\n");
    sll_foreach(o, list) {
        printf("%d", void2(int, o));
    }

}