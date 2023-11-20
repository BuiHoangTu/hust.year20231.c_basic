//
// Created by bhtuw on 20/11/2023.
//
# include "core/heap.h"

void *copy2heap(void *data, size_t data_size)
{
    void *p = malloc(data_size);
    memcpy(p, data, data_size);
    return p;
}