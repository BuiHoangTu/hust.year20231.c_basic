//
// Created by tu on 04/12/2023.
//

#include "binary_search.h"
int _binarySearch(void* arr[], int leftI, int rightI, void *target, CompareFunction compare) {
    while (leftI <= rightI) {
        int current = leftI + (rightI - leftI) / 2;
        if (compare(arr[current], target) == 0)
            return current;

        if (compare(arr[current], target) < 0)
            leftI = current + 1;
        else
            rightI = current - 1;
    }
    return -1;
}


int binarySearch(void **arr, int n, void *target, CompareFunction compare) {
    return _binarySearch(arr, 0, n - 1, target, compare);
}

