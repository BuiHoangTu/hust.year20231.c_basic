#include "sort/quick_sort.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    ArrayList *list = createArraylist();

    arraylistAddLast(list, "abc");
    arraylistAddLast(list, "abb");
    arraylistAddLast(list, "acb");
    arraylistAddLast(list, "aa");
    arraylistAddLast(list, "");

    quickSortArrayList(list, (CompareFunction) strcmp);

    printf("printing\n");
    repeat(i, list->length) {
        printf("%s --", (char*) (list->content[i]));
    }

    return 0;
}
