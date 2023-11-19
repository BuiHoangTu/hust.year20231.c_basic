#ifndef DLL_H_
#define DLL_H_


#include "list/single_linked_list.h"

typedef struct dln
{
	struct sln base;
	struct dln* prev;
} DoubleLinkedNode;

typedef struct dll
{
	struct sll base;
} DoubleLinkedList;

DoubleLinkedList* dll_create();

void dll_add_last(DoubleLinkedList* list, void* value);

int dll_insert(DoubleLinkedList* list, void* value, int index);

void* dll_get(DoubleLinkedList* list, int index);

void* dll_remove(DoubleLinkedList* list, int index);

/**
 * Move node to next node and obj to the value of the next node
 * @param node: address of pointer to the current node
 * @param obj: address of pointer to the variable to store value
 * @return 1: if the operation success
 *         0: if node is already the last node
*/
int dll_next(DoubleLinkedNode** node, void** obj) {
	return sll_next((SingleLinkedNode**)node, obj);
}

/**
 * Move node to previous node and obj to the value of the previous node
 * @param node: address of pointer to the current node
 * @param obj: address of pointer to the variable to store value
 * @return 1: if the operation success
 *         0: if node is already the first node
*/
int dll_prev(DoubleLinkedNode** node, void** obj);

#define dll_foreach(obj, list)             \
	SingleLinkedNode *_node = ((SingleLinkedList* )list)->first; \
	void *obj;                             \
	while (sll_next(&_node, &obj))

void dll_free(SingleLinkedList* list);


#endif // !DLL_H_