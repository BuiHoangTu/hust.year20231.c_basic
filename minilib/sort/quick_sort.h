#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "core/type.h"
#include "array/array_list.h"

void quickSort(void* arr[], int n, CompareFunction compare);

void quickSortArrayList(ArrayList *list, CompareFunction compare);

#endif //QUICK_SORT_H
