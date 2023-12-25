//
// Created by tu on 18/12/2023.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include "map/hash_map.h"
#include "core/hash.h"

int hashStr(char* str) {
    return hashString(str);
}

int strCom(char** str1, char** str2) {
    return strcmp(*str1, *str2);
}

int main() {
    char *line = (char*)malloc(25);
    HashMap *map = createHashmap((HashFunction) hashStr, (CompareFunction) strcmp);
    FILE *source = fopen("test_source.txt", "r");

    if (source == NULL) {
        getcwd(line, 25);
        printf(line);
        exit(1);
    }



    // read until eof
    int n = 0;
    char c = ' ';
    int x = 0;
    while (1) {
        c = fgetc(source);

        // if not char, treat as \0
        if (c == '\n' || c == ' ' || c == '\r' || c == EOF) {
            // if not in word yet, skip
            if (n > 0) {
                line[n++] = '\0';

                // try to get from map
                void *countVal = hashmapGet(map, line);

                printf("%d", x++);

                // if not exist, put to map
                if (countVal == NULL) {
                    char *word = strndup(line, n + 5);
                    int count = 1;

                    hashmapPut(map, word, copy2heap(&count, sizeof(int)));
                } else {
                    // increase count in map
                    (*(int *) countVal) += 1;
                }
            }

            // start over new word
            n = 0;
        } else line[n++] = c;

        if (c == EOF) break;
    }

    ArrayList *list = keySet(map);
    qsort(list->content, list->length, sizeof(void*), (__compar_fn_t) strCom);

    for (int i = 0; i < list->length; i ++) {
        printf("%s %d\n", (char*) list->content[i], void2(int, hashmapGet(map, list->content[i])));
    }
}

