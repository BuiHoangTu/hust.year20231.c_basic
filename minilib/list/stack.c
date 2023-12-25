#include "list/stack.h"


Stack* createStack() {
    return CreateSll();
}

void stackPush(Stack* stack, void* value) {
    sllInsert(stack, value, 0);
}

void* stackPop(Stack* stack) {
    return sllRemove(stack, 0);
}

void* stackPeek(Stack* stack) {
    return sllGet(stack, 0);
}

void stackFree(Stack* stack) {
    sllFree(stack);
}