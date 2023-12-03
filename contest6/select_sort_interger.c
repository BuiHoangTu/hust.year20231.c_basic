//
// Created by bhtuw on 20/11/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "sort/merge_sort.h"

int intcmp(const void* v1, const void* v2) {
    int i1 = *((int*)v1);
    int i2 = *((int*)v2);
    return i1-i2;
}

int main(int argc, const char *argv[]) {
    int n;
    scanf("%d", &n);

    int* array = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i ++) {
        scanf("%d", array+i);
    }

    qsort(array, n, sizeof(int),  intcmp);

    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
}