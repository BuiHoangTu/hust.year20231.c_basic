#ifndef STACK_H_
#define STACK_H_


#include "single_linked_list.h"

#define Stack SingleLinkedList

Stack* createStack();

void stackPush(Stack* stack, void* value);

void* stackPop(Stack* stack);

void* stackPeek(Stack* stack);

void stackFree(Stack* stack);


#endif // STACK_H_