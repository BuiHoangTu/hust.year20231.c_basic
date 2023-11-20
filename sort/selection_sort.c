//
// Created by bhtuw on 20/11/2023.
//

#include "selection_sort.h"

void selectionSort(void *arr[], size_t arrSize, CompareFunction compareFunction) {
    for (int i = 0; i < arrSize; i++) {
        int minIdx = i;

        for (int j = i + 1; j < arrSize; j++) {
            if (compareFunction(arr[i], arr[j] ) > 0) {
                minIdx = j;
            }
        }

        void *tmp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = tmp;
    }
}
