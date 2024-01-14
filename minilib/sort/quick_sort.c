#include "quick_sort.h"

int partition(void *arr[], int low, int high, CompareFunction compare)
{
    int pivotIdx = high;
    void *pivot = arr[pivotIdx];

    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        // current < pivot
        if (compare(arr[j], pivot) < 0)
        {
            i++;
            // swap
            void *tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    void *tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return i + 1;
}

void sortPartition(void *arr[], int low, int high, CompareFunction compare)
{
    if (low < high)
    {
        int pivotIdx = partition(arr, low, high, compare);

        sortPartition(arr, low, pivotIdx - 1, compare);
        sortPartition(arr, pivotIdx + 1, high, compare);
    }
}

void quickSort(void *arr[], int n, CompareFunction compare)
{
    sortPartition(arr, 0, n - 1, compare);
}

void quickSortArrayList(ArrayList *list, CompareFunction compare)
{
    quickSort(list->content, list->length, compare);
}
