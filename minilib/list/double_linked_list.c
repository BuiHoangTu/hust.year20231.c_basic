#include "list/double_linked_list.h"
#include "list/single_linked_list.c"

#define toDLL(list) ((DoubleLinkedList *)list)
#define toSLL(list) ((SingleLinkedList *)list)
#define toSLN(node) ((SingleLinkedNode *)node)
#define toDLN(node) ((DoubleLinkedNode *)node)

DoubleLinkedList *CreateDll()
{
    DoubleLinkedList *list = toDLL(malloc(sizeof(DoubleLinkedList)));
    toSLL(list)->first = NULL;
    toSLL(list)->last = NULL;
    toSLL(list)->length = 0;

    return list;
}

void __dll_add_node_last(DoubleLinkedList *list, DoubleLinkedNode *node)
{
    list->base.length++;
    // empty list
    if (list->base.first == NULL)
    {
        list->base.first = list->base.last = toSLN(node);
    }
    else
    {
        // add node to last node
        list->base.last->next = toSLN(node);
        // add last node to prev of this node
        node->prev = toDLN(list->base.last);
        // move last of list to this
        list->base.last = toSLN(node);
    }
}

int __dll_insert_node(DoubleLinkedList *list, DoubleLinkedNode *node, int index)
{
    if (index == 0)
    {
        // add first node to this node
        toSLN(node)->next = toSLL(list)->first;
        // add this node to first node
        toDLN(toSLL(list)->first)->prev = node;
        // move first node holder to this
        toSLL(list)->first = toSLN(node);
        return 1;
    }

    SingleLinkedNode *current = __sll_get_node(toSLL(list), index);

    toSLN(node)->next = current->next;
    node->prev = toDLN(current);

    current->next = toSLN(node);
    return 1;
}

DoubleLinkedNode *dln_create(void *value)
{
    DoubleLinkedNode *node = (DoubleLinkedNode *)malloc(sizeof(DoubleLinkedNode));
    toSLN(node)->next = NULL;
    toSLN(node)->value = value;
    node->prev = NULL;
    return node;
}

void DllAddLast(DoubleLinkedList *list, void *value)
{
    __dll_add_node_last(list, dln_create(value));
}

int dllInsert(DoubleLinkedList *list, void *value, int index)
{
    if (index > toSLL(list)->length)
        return 0;

    toSLL(list)->length++;
    DoubleLinkedNode *newNode = dln_create(value);

    if (toSLL(list)->length == index)
    {
        __dll_add_node_last(list, newNode);
        return 1;
    }

    return __dll_insert_node(list, newNode, index);
}

void *dllGet(DoubleLinkedList *list, int index)
{
    return __sll_get_node(toSLL(list), index);
}

void *dllRemove(DoubleLinkedList *list, int index)
{
    if (index >= toSLL(list)->length)
        return NULL;

    DoubleLinkedNode *current = toDLN(__sll_get_node(toSLL(list), index));

    if (current->base.next != NULL) {
        toDLN(current->base.next)->prev = current->prev;
        
    }

    if (current->prev != NULL)
    {
    }

    SingleLinkedNode *first = list->base.first;
    SingleLinkedNode *second = first->next;

    list->base.first = second;
    toDLN(second)->prev = NULL;

    void *value = first->value;
    free(first);
    return value;
}

int dllPrev(DoubleLinkedNode **node, void **obj)
{
    if ((*node) == NULL)
        return 0;

    *obj = toSLN(*node)->value;
    (*node) = (*node)->prev;

    return 1;
}

void dllFree(SingleLinkedList *list)
{
    free(list);
}
