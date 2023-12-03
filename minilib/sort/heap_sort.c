//
// Created by tu on 02/12/2023.
//
#include "heap_sort.h"
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(void *arr[], int n, int i, CompareFunction compare)
{
    // Find largest among root,
    // left child and right child

    // Initialize largest as root
    int largestIndex = i;

    // left = 2*i + 1
    int leftIndex = 2 * i + 1;

    // right = 2*i + 2
    int rightIndex = 2 * i + 2;

    // If left child is larger than root
    if (leftIndex < n && compare(arr[leftIndex], arr[largestIndex]) > 0)
        largestIndex = leftIndex;

    // If right child is larger than largest
    // so far
    if (rightIndex < n && compare(arr[rightIndex], arr[largestIndex]) > 0)
        largestIndex = rightIndex;

    // Swap and continue heapify
    // if root is not the largest
    // If largest is not root
    if (largestIndex != i) {
        void *tmpV = arr[i];
        arr[i] = arr[largestIndex];
        arr[largestIndex] = tmpV;

        // Recursively heapify the affected
        // subtree
        heapify(arr, n, largestIndex, compare);
    }
}

void heapSort(void *arr[], size_t arrSize, CompareFunction compareFunction) {
    // build max heap
    for (int i = (arrSize / 2) - 1; i >= 0; i-- ) {
        heapify(arr, arrSize, i, compareFunction);
    }

    // sort
    for (int i = arrSize - 1; i >= 0; i--) {
        void *tmpV = arr[0];
        arr[0] = arr[i];
        arr[i] = tmpV;

        // Heapify root element
        // to get highest element at
        // root again
        heapify(arr, i, 0, compareFunction);
    }
}

