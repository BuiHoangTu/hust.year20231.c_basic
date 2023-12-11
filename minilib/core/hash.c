//
// Created by tu on 12/11/23.
//

#include "hash.h"

int hashInt(void *vi) {
    int value = void2(int, vi);
    value ^= value >> 16;
    value *= 0x85ebca6b;
    value ^= value >> 13;
    value *= 0xc2b2ae35;
    value ^= value >> 16;
    return value;
}

int hashVoid(void *v, size_t size) {
    int hash = 17;

    char *c = (char*)v;

    for (int i = 0; i < size; i++) {
        hash = (hash * 33) ^ c[i];
    }

    return hash;
}

int hashString(const char *c) {
    int hash = 17;

    for (int i = 0; c[i] != '\0'; i++) {
        hash = (hash * 33) ^ c[i];
    }

    return hash;
}
