#ifndef SLL_H_
#define SLL_H_

#include <stdlib.h>

typedef struct sln
{
	void *value;
	struct sln *next;
} SingleLinkedNode;

typedef struct sll
{
	int length;
	SingleLinkedNode *first;
	SingleLinkedNode *last;
} SingleLinkedList;

/**
 * Create a SingleLinkedList
*/
SingleLinkedList *CreateSll();

/**
 * Add an object to the last part of the list 
*/
void sllAddLast(SingleLinkedList *list, void *value);

/**
 * Add an object at the index 
 * @return 1: success; 0: index out of bound
*/
int sllInsert(SingleLinkedList *list, void *value, int index);

/**
 * Get an object at the index
*/
void *sllGet(SingleLinkedList *list, int index);

/**
 * Remove an object at index, return that object 
*/
void *sllRemove(SingleLinkedList *list, int index);

/**
 * Move node to next node and obj to the value of the next node
 * @param node: address of pointer to the current node 
 * @param obj: address of pointer to the variable to store value
 * @return 1: if the operation success
 *         0: if node is already the last node
*/
int sll_next(SingleLinkedNode **node, void **obj);

#define sll_foreach(obj, list)             \
	SingleLinkedNode *_node = list->first; \
	void *obj;                             \
	while (sll_next(&_node, &obj))

void sllFree(SingleLinkedList* list);

#endif // SLL_H_