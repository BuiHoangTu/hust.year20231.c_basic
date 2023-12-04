//
// Created by tu on 04/12/2023.
//
#ifndef INYEAR4_1_BINARY_SEARCH_H
#define INYEAR4_1_BINARY_SEARCH_H

#include "core/type.h"
/**
 * Find the target index in the array
 * @param arr the array
 * @param n length of array
 * @param target pointer to target
 * @param compare how to compare each elemnt in array with target
 * @return index of target in array <br> an int that less than 0 if cant find target in array
 */
int binarySearch(void *arr[], int n, void *target, CompareFunction compare);

#endif //INYEAR4_1_BINARY_SEARCH_H
