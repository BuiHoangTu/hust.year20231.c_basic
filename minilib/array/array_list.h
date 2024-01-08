//
// Created by bhtuw on 19/11/2023.
//

#ifndef MINI_LIBRARY_ARRAY_LIST_H
#define MINI_LIBRARY_ARRAY_LIST_H

typedef struct
{
    int length;
    int capacity;
    void **content;
} ArrayList;


ArrayList *createArraylist();


/**
 * Add an object to a list
 */
void arraylistAddLast(ArrayList *list, void *object);

/**
 * Insert an object to the specified position
 */
void arraylistInsert(ArrayList *list, int index, void *obj);

/**
 * Get object at index
 */
void *arraylistGet(ArrayList *list, int index);

/**
 * Remove and return element so user can free it if needed
 */
void *arraylistRemove(ArrayList *list, int index);

void _arraylistNext(ArrayList *list, int *index, void **obj);

/**
 * foreach object in the list, you do thing
 */
#define arraylist_foreach(obj, list) \
    int _i = 0;            \
    for (void *obj = list->content[0]; _i < list->length; _arraylist_next(list, &_i, &obj))

void freeArraylist(ArrayList *list);

#endif //MINI_LIBRARY_ARRAY_LIST_H
