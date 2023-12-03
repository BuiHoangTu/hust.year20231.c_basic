//
// Created by bhtuw on 27/11/2023.
//
//
// Created by bhtuw on 20/11/2023.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "core/heap.h"


typedef struct {
    char *ten;
    char *date;
} Document;

int docCmp (const void *d1, const void* d2) {
    Document *doc1 = (*(Document**) d1);
    Document *doc2 = (*(Document**)d2);

    // cmp name
    char* fullName1 = doc1->ten;
    char* fullName1Dup = strdup(fullName1);
    char *tmp1 = strtok(fullName1Dup, " ");
    char *name1;
    while (tmp1) {
        name1 = tmp1;
        tmp1 = strtok(NULL, " ");
    }

    char* fullName2 = doc2->ten;
    char* fullName2Dup = strdup(fullName2);
    char *tmp2 = strtok(fullName2Dup, " ");
    char *name2;
    while (tmp2) {
        name2 = tmp2;
        tmp2 = strtok(NULL, " ");
    }

    int res = strcmp(name1, name2);
    free(fullName1Dup);
    free(fullName2Dup);

    if (res != 0) return res;

    // cmp full name
    res = strcmp(fullName1, fullName2);
    if (res != 0) return res;

    // cmp date
    return strcmp(doc1->date, doc2->date);
}

int main() {
    char *line = (char*) malloc(1024);

    int n  = 0;
    Document **arr = (Document**) malloc(1024 * sizeof(Document*));

    while (1) {
        fgets(line, 1024, stdin);
        if (strncmp(line, "#", 1) == 0) break;

        char *name = strdup(line);

        fgets(line, 1024, stdin);
//        int yyyy, mm, dd;
//        sscanf(line, "%d-%d-%d", &yyyy, &mm, &dd);

        Document *document = (Document*) malloc(sizeof (Document));
        document->ten = name;
//        document->yyyy = yyyy;
//        document->mm = mm;
//        document->dd = dd;
        document->date = strdup(line);

        arr[n] = document;

        n ++;

    }

    free(line);

    qsort(arr, n, sizeof(Document*), docCmp);


    for (int i = 0; i < n; i ++) {
        printf("%s%s", void2(Document, arr[i]).ten, void2(Document, arr[i]).date);
    }

    printf("#");
}