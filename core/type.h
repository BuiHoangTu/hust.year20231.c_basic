#ifndef TYPE_H_
#define TYPE_H_

#include "core/heap.h"

/**
 * A function defining how 2 compare unk variable (generic structure)
 */
typedef int (*CompareFunction)(void *, void *);

typedef void (*Action)();

typedef void (*Processor0)();

typedef void (*Processor1)(void *);

/**
 *
 */
int intCmp(void *v1, void *v2)
{
    int i1 = void2(int, v1);
    int i2 = void2(int, v2);

    return i1 - i2;
}

#endif // TYPE_H_