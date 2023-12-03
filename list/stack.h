#ifndef STACK_H_
#define STACK_H_


#include "single_linked_list.h"

#define Stack SingleLinkedList

Stack* stack_create();

void stack_push(Stack* stack, void* value);

void* stack_pop(Stack* stack);

void* stack_peek(Stack* stack);

void stack_free(Stack* stack);


#endif // STACK_H_