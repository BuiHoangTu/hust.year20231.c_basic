//
// Created by bhtuw on 27/11/2023.
//

#include "stdlib.h"
#include "stdio.h"
#include "sort/heap_sort.h"

int cmp(void *v1, void *v2) {
    int i1 = *((int*) v1);
    int i2 = *((int*) v2);

    return i1 - i2;
}

int main() {
    int n;
    scanf("%d", &n);

    void **arr = (void*) malloc(n * sizeof(void*));

    int x;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);

        arr[i] = copy2heap(&x,sizeof(int));
    }

    heapSort(arr,n,cmp);

    for (int i = 0; i < n; ++i) {
        printf("%d ", void2(int, arr[i]));
    }
}