//
// Created by bhtuw on 20/11/2023.
//

#include "core/type.h"

int intCmp(void *v1, void *v2)
{
    int i1 = void2(int, v1);
    int i2 = void2(int, v2);

    return i1 - i2;
}