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
int intCmp(void *v1, void *v2);

#endif // TYPE_H_