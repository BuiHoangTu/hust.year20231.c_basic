//
// Created by tu on 12/11/23.
//

#ifndef INYEAR4_1_HASH_MAP_H
#define INYEAR4_1_HASH_MAP_H

#include "array/array_list.h"
#include "core/type.h"

/**
 * @param size: how many elements are in the map <br>
 * @param capacity: length of content <br>
 * @param content: array of array_list <br>
 * @param hashFunction: how to hash a key
 * @param compareFunction: how to compare 2 key
 */
typedef struct hash_map {
    ArrayList** content;
    int size;
    int capacity;
    HashFunction hashFunction;
    CompareFunction compareFunction;
}HashMap;

HashMap *createHashmap(HashFunction hashFunction, CompareFunction compareFunction);

/**
 * Insert value to map
 * @param map
 * @param key
 * @param value new value
 * @param compare compare 2 key
 * @return old value if key existed <br>
 * NULL if no existed key
 */
void *hashmapPut(HashMap *map, void *key, void *value);

void *hashmapGet(HashMap *map, void *key);

ArrayList *keySet(HashMap *map);

void freeHashmap(HashMap* map, Consume1 freeKey, Consume1 freeValue);

#endif //INYEAR4_1_HASH_MAP_H
