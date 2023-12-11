//
// Created by tu on 12/11/23.
//
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include "core/heap.h"
#include "search/binary_search.h"

typedef struct hssv {
    char* name;
    char* email;
}Document;

int hssvCmp(const void *v1, const void* v2) {
    Document *d1 = void2(Document*, v1);
    Document *d2 = void2(Document*, v2);

    return strcmp(d1->name, d2->name);
}

int main() {
    int n  = 0;
    Document **arr = (Document**) malloc(1024 * sizeof(Document*));
    char *line = (char*)malloc(1024);

    while (1) {
        fgets(line, 1024, stdin);
        if (strncmp(line, "#", 1) == 0) break;

        char *buffer = strdup(line);
        char *name = strtok(line, " ");
        char *email = strtok(NULL, " ");

        Document *document = (Document*) malloc(sizeof (Document));
        document->name = name;
        document->email = email;

        arr[n] = document;

        n ++;

    }

    qsort(arr, n, sizeof(void*), hssvCmp);
    Document target;
    target.name = "";
    int res = binarySearch((void **) arr, n, &target, (CompareFunction) hssvCmp);

    free(line);
}