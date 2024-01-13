#ifndef TYPE_H_
#define TYPE_H_

#include "core/heap.h"

#define repeat(var_name, times) for (int var_name = 0; var_name < times; var_name ++)

/**
 * A function defining how 2 compare unk variable (generic structure)
 */
typedef int (*CompareFunction)(void *, void *);

/**
 * An action
 */
typedef void (*Action)();

/**
 * Consume 1 void data to do something <br>
 * Ex: free pointer, print pointer
 */
typedef void (*Consume1)(void *);

/**
 * Hash a void data
 */
typedef int (*HashFunction)(void *);

/**
 * Compare 2 data
 */
int intCmp(void *v1, void *v2);

#endif // TYPE_H_