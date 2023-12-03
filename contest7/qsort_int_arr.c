//
// Created by bhtuw on 27/11/2023.
//

#include "stdlib.h"
#include "stdio.h"

int cmp(const void *v1, const void *v2) {
    int i1 = *((int*) v1);
    int i2 = *((int*) v2);

    return i1 - i2;
}

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    qsort(arr,
          n,
          sizeof(int),
          cmp);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
}