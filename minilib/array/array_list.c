//
// Created by bhtuw on 19/11/2023.
//

#include "array/array_list.h"
#include <stdlib.h>
#include <string.h>

#define MIN_CAPACITY 10
#define ALLOCATE_THRESHOLD (100 / 100)
#define ALLOCATE_RATIO 2

void _arr_enlarge(ArrayList *list)
{
    if (list->length >= list->capacity * ALLOCATE_THRESHOLD)
    {
        list->capacity *= ALLOCATE_RATIO;
        list->content = realloc(list->content, list->capacity * sizeof(void *));
    }
}

ArrayList *createArraylist()
{
    /* Allocate Memory */
    ArrayList *list = malloc(sizeof(ArrayList));
    if (list == NULL)
        return NULL;

    // initialize fields
    list->capacity = MIN_CAPACITY;
    list->length = 0;
    list->content = calloc(MIN_CAPACITY, sizeof(void *)); // content = array of pointer
    return list;
}

void _arraylistNext(ArrayList *list, int *index, void **obj)
{
    (*index)++;
    *obj = list->content[*index];
}

void arraylistAddLast(ArrayList *list, void *object)
{
    // need bigger size
    _arr_enlarge(list);

    /* Adds one element of generic pointer type to the internal array */
    list->content[list->length] = object;
    list->length += 1;
}

void arraylistInsert(ArrayList *list, int index, void *obj)
{
    // bigger size
    _arr_enlarge(list);

    memcpy(list->content + index + 1, list->content + index, list->length - index);
    list->content[index] = obj;
    list->length++;
}

void *arraylistGet(ArrayList *list, int index)
{
    /* Gets an member of the array at an index */
    return list->content[index];
}

void *arraylistRemove(ArrayList *list, int index)
{
    /* Removes one element at and index */
    if (index > list->length - 1)
        return NULL;

    void *del_elem = list->content[index];
    list->length--;
    // move all back elem forward
    memcpy(list->content + index, list->content + index + 1, list->length - index);
    return del_elem;
}

void freeArraylist(ArrayList *list)
{
    /* Clears the internal array */
    free(list->content);
    free(list);
}
