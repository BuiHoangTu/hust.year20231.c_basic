//
// Created by bhtuw on 27/11/2023.
//

#include "merge_sort.h"

// Merges two sub-arrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(void *arr[], int l, int m, int r, CompareFunction compare)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    void** L = (void**) malloc(sizeof(void*) * n1);
    void** R = (void**) malloc(sizeof(void*) * n2);

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    free(L);

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(R);
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void sortSubArray(void *arr[], int l, int r, CompareFunction pFunction)
{
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        sortSubArray(arr, l, m, pFunction);
        sortSubArray(arr, m + 1, r, pFunction);

        merge(arr, l, m, r, pFunction);
    }
}

void mergeSort(void *arr[], int n, CompareFunction compare) {
    sortSubArray(arr, 0, n - 1, compare);
}