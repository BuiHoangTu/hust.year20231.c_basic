//
// Created by tu on 04/12/2023.
//

#include "stdio.h"
#include "stdlib.h"
#include "core/heap.h"
#include "search/binary_search.h"

int qsort_cmp(const void *v1, const void *v2) {
    int i1 = *void2(int*, v1);
    int i2 = *void2(int*, v2);

    return i1 - i2;
}

/**
 * Given a sequence of distinct elements a1, a2, …, aN and a value b. Count the number Q of pairs (ai, aj) having ai + aj = b (i < j).InputLine 1: contains an integer n and b (1 <= n <= 106, 1 <= b <= 109)Line 2: contains a1, a2, …, aN (1 <= ai <= 106)OutputWrite the value of Q
 */
int main() {
    int n, b;
    scanf("%d %d", &n, &b);

    int **arr = (int**) malloc(n * sizeof(int*));
    int *intArr = (int*) malloc(n * sizeof(int));

    int tmp;
    for (int i = 0; i < n; i ++) {
        arr[i] = intArr + i;

        scanf("%d", arr[i]);

    }

    qsort(arr, n, sizeof(int*), qsort_cmp);

//    for (int i = 0; i < n; i++) {
//        printf("%d ", void2(int, arr[i]));
//    }

    int q = 0;
    for (int i = 0; i < n - 1; i ++) {
        int target = b - *arr[i];

        int res = binarySearch((void **) (arr + i + 1), n - i - 1, &target, intCmp);

        if (res >= 0) q ++;
    }

    printf("%d", q);
}