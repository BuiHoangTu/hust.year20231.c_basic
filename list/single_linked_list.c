#include "single_linked_list.h"

SingleLinkedList *sll_create()
{
	SingleLinkedList *list = (SingleLinkedList *)malloc(sizeof(SingleLinkedList));
	list->first = NULL;
	list->last = NULL;
	list->length = 0;

	return list;
}

/**
 * Get node at index
 */
SingleLinkedNode *__sll_get_node(SingleLinkedList *list, int index)
{
	if (index >= list->length) return NULL;

	SingleLinkedNode *current = list->first;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current;
}

/**
 * add node to the last, increase length
 */
void __sll_add_node_last(SingleLinkedList *list, SingleLinkedNode *node)
{
	// increase length
	list->length++;
	// if empty list
	if (list->first == NULL)
	{
		// add node to both first and last
		list->first = list->last = node;
	}
	else // add node after last
	{
		list->last->next = node;
		list->last = node;
	}
}

/**
 * insert node at index, increase length
 */
int __sll_insert_node(SingleLinkedList *list, SingleLinkedNode *node, int index)
{
	if (index > list->length) return 0;

	// if insert at first
	if (index == 0)
	{
		node->next = list->first;
		list->first = node;
		list->length++;
		return 1;
	}
	// insert last 
	else if (index == list->length)
	{
		// this function increase already
		__sll_add_node_last(list, node);
		return 1;
	} 
	else
	{
		// add node at middle
		SingleLinkedNode *current = __sll_get_node(list, index - 1);
		// add next node
		node->next = current->next;
		// add this node
		current->next = node;
		list->length++;
		return 1;
	}
}

/**
 * remove a node, decrease length, free the node
 * @param prevNode: the node before the node need removing
 * @return value that the node holds
 */
void *__sll_remove_node(SingleLinkedList *list, SingleLinkedNode *node, SingleLinkedNode *prevNode)
{
	// node is first node
	if (prevNode == NULL)
	{
		list->first = node->next;
	}
	// node is the last node
	else if (node->next == NULL)
	{
		prevNode->next = NULL;
		list->last = prevNode;
	}
	// node is in the middle 
	else
	{
		prevNode->next = node->next;
	}

    list->length--;
	void *value = node->value;
	free(node);
	return value;
}

SingleLinkedNode *sln_create(void *value)
{
	SingleLinkedNode *node = (SingleLinkedNode *)malloc(sizeof(SingleLinkedNode));
	node->next = NULL;
	node->value = value;
	return node;
}

void sll_add_last(SingleLinkedList *list, void *value)
{
	SingleLinkedNode *newNode = sln_create(value);
	__sll_add_node_last(list, newNode);
}

int sll_insert(SingleLinkedList *list, void *value, int index)
{
	SingleLinkedNode *newNode = sln_create(value);
	return __sll_insert_node(list, newNode, index);
}

void *sll_get(SingleLinkedList *list, int index)
{
	SingleLinkedNode* node = __sll_get_node(list, index);
	return node == NULL ? NULL : node->value;
}

void *sll_remove(SingleLinkedList *list, int index)
{
	if (index >= list->length)
		return NULL;

	if (index == 0)
	{
		return __sll_remove_node(list, list->first, NULL);
	}

	SingleLinkedNode *prev = __sll_get_node(list, index - 1);
	SingleLinkedNode *current = prev->next;

	return __sll_remove_node(list, current, prev);
}

int sll_next(SingleLinkedNode **node, void **obj)
{
    if ((*node) == NULL)
        return 0;

    *obj = (*node)->value;
    (*node) = (*node)->next;

    return 1;
}

void sll_free(SingleLinkedList *list)
{
	free(list);
}
