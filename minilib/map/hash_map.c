//
// Created by tu on 12/11/23.
//

#include "hash_map.h"
#include "array/array_list.h"
#include "stdlib.h"

#define DEFAULT_MAP_SIZE 100
#define MAP_SCALE 2

typedef struct entry{
    void *key;
    void *value;
    int hashCode;
}Entry;

void hashmapInitContent(HashMap *map) {
    map->content = (ArrayList**) malloc(map->capacity * sizeof(ArrayList*));
    for (int i = 0; i < map->capacity; i++) {
        map->content[i] = createArraylist();
    }
}

void hashmapFreeContent(ArrayList **content, int length, Consume1 freeKey, Consume1 freeValue, int doFreeEntry) {
    for (int i = 0; i < length; ++i) {
        ArrayList *bucket = content[i];
        if (doFreeEntry) {
            for (int j = 0; j < bucket->length; j++) {
                // free each entry, key, val
                Entry *entry = (Entry *) arraylistGet(bucket, j);
                if (freeKey) freeKey(entry->key);
                if (freeValue) freeValue(entry->value);
                free(entry);
            }
        }
        freeArraylist(bucket);
    }

    free(content);
}

void enlargeHashmap(HashMap *map) {
    // get old length and map
    int oldCapacity = map->capacity;
    ArrayList **oldContent = map->content;

    // enlarge content
    map->capacity *= MAP_SCALE;
    hashmapInitContent(map);

    // move old content
    for (int i = 0; i < oldCapacity; i++) {
        ArrayList *oldBucket = oldContent[i];
        for (int j = 0; j < oldBucket->length; j++) {
            Entry *entry = (Entry*) oldBucket->content[j];
            int newIndex = abs(entry->hashCode % map->capacity);
            arraylistAddLast(map->content[newIndex], entry);
        }
    }

    // free old content
    hashmapFreeContent(oldContent, oldCapacity, NULL, NULL, 0);
}

HashMap *createHashmap(HashFunction hashFunction, CompareFunction compareFunction) {
    HashMap *map = (HashMap*)malloc(sizeof(HashMap));

    map->capacity = DEFAULT_MAP_SIZE;

    hashmapInitContent(map);

    map->compareFunction = compareFunction;
    map->hashFunction = hashFunction;
    map->size = 0;

    return map;
}

void *hashmapPut(HashMap *map, void *key, void *value) {
    if (map->size >= map->capacity) {
        enlargeHashmap(map);
    }

    int hashCode = map->hashFunction(key);
    int index = abs(hashCode % map->capacity);
    ArrayList *bucket = map->content[index];

    // search for key in bucket, if exists, replace
    for (int i = 0; i < bucket->length; i++) {
        Entry *entry = (Entry*) arraylistGet(bucket, i);
        // check key equal key
        if (entry->key == key || map->compareFunction(entry->key, key) == 0) {
            void *oldValue = entry->value;
            entry->value = value;
            return oldValue;
        }
    }

    // if not exist, add entry
    Entry *newEntry = (Entry*) malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->hashCode = hashCode;
    arraylistAddLast(bucket, newEntry);

    map->size += 1;
    return NULL;
}

void *hashmapGet(HashMap *map, void *key) {
    int hashCode = map->hashFunction(key);
    int index = abs(hashCode % map->capacity);
    ArrayList* bucket = map->content[index];

    // Check if the key exists in the bucket
    for (int i = 0; i < bucket->length; ++i) {
        Entry *entry = (Entry*) arraylistGet(bucket, i);
        // check key equal key
        if (entry->key == key || map->compareFunction(entry->key, key) == 0) {
            // Key found, return the associated value
            return entry->value;
        }
    }

    // Key not found
    return NULL;
}

void freeHashmap(HashMap *map, Consume1 freeKey, Consume1 freeValue) {
    if (map == NULL) {
        return;
    }

    hashmapFreeContent(map->content, map->capacity, freeKey, freeValue, 1);

    free(map);
}

ArrayList *keySet(HashMap *map) {
    ArrayList *list = createArraylist();

    for (int i = 0; i < map->capacity; ++i) {
        ArrayList *bucket = map->content[i];
        for (int j = 0; j < bucket->length; j++) {
            Entry *entry = (Entry*) arraylistGet(bucket, j);
            arraylistAddLast(list, entry->key);
        }
    }

    return list;
}


