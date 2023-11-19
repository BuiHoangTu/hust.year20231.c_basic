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


ArrayList *arraylist_create();


/**
 * Add an object to a list
 */
void arraylist_add_last(ArrayList *list, void *object);

/**
 * Insert an object to the specified position
 */
void arraylist_insert(ArrayList *list, int index, void *obj);

/**
 * Get object at index
 */
void *arraylist_get(ArrayList *list, int index);

/**
 * Remove and return element so user can free it if needed
 */
void *arraylist_remove(ArrayList *list, int index);

void _arraylist_next(ArrayList *list, int *index, void **obj);

/**
 * foreach object in the list, you do thing
 */
#define arraylist_foreach(obj, list) \
    int _i = 0;            \
    for (void *obj = list->content[0]; _i < list->length; _arraylist_next(list, &_i, &obj))

void arraylist_free(ArrayList *list);

#endif //MINI_LIBRARY_ARRAY_LIST_H
