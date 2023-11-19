#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>
#include <string.h>

#define quickCalloc(type, variable) type *variable = (type *) calloc (1, sizeof(type))

#define void2(type, pointer) (*((type *)pointer))

void *copy2heap(void *data, size_t data_size)
{
    void *p = malloc(data_size);
    memcpy(p, data, data_size);
    return p;
}

#endif // HEAP_H_